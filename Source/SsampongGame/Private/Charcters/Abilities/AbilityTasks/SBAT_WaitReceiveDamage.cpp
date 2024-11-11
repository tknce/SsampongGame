// Fill out your copyright notice in the Description page of Project Settings.


#include "Charcters/Abilities/AbilityTasks/SBAT_WaitReceiveDamage.h"

#include "Charcters/Abilities/SAbilitySystemComponent.h"

USBAT_WaitReceiveDamage::USBAT_WaitReceiveDamage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TriggerOnce = false;
}

USBAT_WaitReceiveDamage* USBAT_WaitReceiveDamage::WaitReceiveDamage(UGameplayAbility* OwningAbility, bool InTriggerOnce)
{
	USBAT_WaitReceiveDamage* MyObj = NewAbilityTask<USBAT_WaitReceiveDamage>(OwningAbility);
	MyObj->TriggerOnce = InTriggerOnce;
	return MyObj;
}

void USBAT_WaitReceiveDamage::Activate()
{
	USAbilitySystemComponent* GDASC = Cast<USAbilitySystemComponent>(AbilitySystemComponent);

	if (GDASC)
	{
		GDASC->ReceivedDamage.AddDynamic(this, &USBAT_WaitReceiveDamage::OnDamageReceived);
	}
}

void USBAT_WaitReceiveDamage::OnDestroy(bool AbilityIsEnding)
{
	USAbilitySystemComponent* GDASC = Cast<USAbilitySystemComponent>(AbilitySystemComponent);

	if (GDASC)
	{
		GDASC->ReceivedDamage.RemoveDynamic(this, &USBAT_WaitReceiveDamage::OnDamageReceived);
	}

	Super::OnDestroy(AbilityIsEnding);
}

void USBAT_WaitReceiveDamage::OnDamageReceived(USAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
	}

	if (TriggerOnce)
	{
		EndTask();
	}
}



