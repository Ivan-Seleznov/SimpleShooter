// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Weapons/ADSAbility.h"

#include "BladeRushLogs.h"
#include "Camera/BladeRushCameraManager.h"
#include "Camera/CameraMode_InterpLocation.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Weapons/BaseWeaponActor.h"
#include "Weapons/WeaponItemInstance.h"


void UADSAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	EndAbility(Handle,ActorInfo,ActivationInfo,true,true);
}

void UADSAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UWeaponItemInstance* WeaponInstance = GetWeaponInstance();
	if (!WeaponInstance)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo,false,true);
		return;
	}

	WeaponInstance->OnEnterADS();
	ActiveGameplayEffectHandle = ApplyGameplayEffect(ADSGameplayEffect);

	ABaseWeaponActor* WeaponActor = WeaponInstance->GetSpawnedWeaponActor();
	if (!WeaponActor || !WeaponActor->GetCameraModeClass())
	{
		return;
	}
	
	if (ABladeRushCameraManager* CameraManager = GetCameraManager())
	{
		UCameraMode_InterpLocation* CameraMode = NewObject<UCameraMode_InterpLocation>(CameraManager,WeaponActor->GetCameraModeClass());
		//CameraMode->SetTargetOffset(WeaponActor->GetAimOffset().);
		CameraManager->SetCameraModeObject(CameraMode);
	}
}

void UADSAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	RemoveGameplayEffectFromActiveHandle(ActiveGameplayEffectHandle);

	UWeaponItemInstance* WeaponInstance = GetWeaponInstance();
	if (!WeaponInstance) return;

	WeaponInstance->OnExitADS();
	if (ABladeRushCameraManager* CameraManager = GetCameraManager())
	{
		CameraManager->ExitCurrentCameraMode();
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

ABladeRushCameraManager* UADSAbility::GetCameraManager() const
{
	APlayerController* PlayerController = Cast<APlayerController>(GetControllerFromActorInfo());
	if (PlayerController)
	{
		return Cast<ABladeRushCameraManager>(PlayerController->PlayerCameraManager);
	}

	return nullptr;
}
