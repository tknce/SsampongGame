// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SBGA_Fire.h"

USBGA_Fire::USBGA_Fire()
{
	Range = 100000.f;
	Damage = 12.f;
}

void USBGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void USBGA_Fire::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void USBGA_Fire::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void USBGA_Fire::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
}

