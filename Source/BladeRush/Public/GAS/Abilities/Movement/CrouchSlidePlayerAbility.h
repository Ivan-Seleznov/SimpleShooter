// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/Movement/MovementAbilityBase.h"
#include "CrouchSlidePlayerAbility.generated.h"

/**
 * 
 */
UCLASS()
class BLADERUSH_API UCrouchSlidePlayerAbility : public UMovementAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual bool CanActivateMovementAbility(ABaseCharacter* Character, UShooterMovementComponent* ShooterMovementComponent) const override;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void ActivateSlide(ABaseCharacter* Character, UShooterMovementComponent* ShooterMovementComponent);
	void ActivateCrouch(ABaseCharacter* Character, UShooterMovementComponent* ShooterMovementComponent);
	
	
	UFUNCTION()
	void MovementModeChanged(ACharacter* Character,EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FShooterGameplayEffect SlideEffect;
private:
	bool bCrouching = false;
};
