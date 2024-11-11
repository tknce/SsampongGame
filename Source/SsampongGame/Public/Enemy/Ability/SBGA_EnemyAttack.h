// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/SBGA_Fire.h"
#include "SBGA_EnemyAttack.generated.h"

class ASBelicaCharacter;
/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API USBGA_EnemyAttack : public USBGA_Fire
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* FireHipMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* FireIronsightsMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ASBelicaCharacter* TargetActor;

	void SetTargetActor(ASBelicaCharacter* actor);
	/** Actually activate ability, do not call this directly. We'll call it from APAHeroCharacter::ActivateAbilitiesWithTags(). */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:
	virtual void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData) override;

	virtual void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData) override;

	virtual void EventReceived(FGameplayTag EventTag, FGameplayEventData EventData) override;

public:
	USBGA_EnemyAttack();
};
