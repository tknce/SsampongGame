// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/SBGA_Fire.h"
#include "Charcters/Abilities/CharacterGameplayAbility.h"
#include "SBelicaGA_Fire.generated.h"

/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API USBelicaGA_Fire : public USBGA_Fire
{
	GENERATED_BODY()
public:
	USBelicaGA_Fire();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* FireHipMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* FireHip2Montage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* FireHip3Montage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* FireIronsightsMontage;

	/** Actually activate ability, do not call this directly. We'll call it from APAHeroCharacter::ActivateAbilitiesWithTags(). */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:
	virtual void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData) override;

	virtual void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData) override;

	virtual void EventReceived(FGameplayTag EventTag, FGameplayEventData EventData) override;
};
