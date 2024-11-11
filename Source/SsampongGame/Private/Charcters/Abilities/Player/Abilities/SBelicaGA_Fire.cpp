// Fill out your copyright notice in the Description page of Project Settings.


#include "Charcters/Abilities/Player/Abilities/SBelicaGA_Fire.h"

#include "AbilitySystemComponent.h"
#include "Charcters/SBelicaPlayerCharacter.h"
#include "Charcters/SBProjectile.h"
#include "Charcters/Abilities/AbilityTasks/SBAT_PlayMontageAndWaitForEvent.h"
#include "Kismet/KismetMathLibrary.h"

USBelicaGA_Fire::USBelicaGA_Fire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Attack"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));

	Range = 1000.0f;
	Damage = 12.0f;
}

void USBelicaGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	ASBelicaPlayerCharacter* Hero = Cast<ASBelicaPlayerCharacter>(GetAvatarActorFromActorInfo());
	UAnimMontage* MontageToPlay = FireHipMontage;
	int combo = Hero->GetComboCount();
	switch (combo)
	{
		case 0 :
			MontageToPlay = FireHipMontage;
			break;
		case 1:
			MontageToPlay = FireHip2Montage;
			break;
		case 2:
			MontageToPlay = FireHip3Montage;
			break;
		default:
		break;
	}
	
	// GetAbilitySystemComponentFromActorInfo()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")), 0);
	if (GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.AimDownSights"))) &&
		!GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.AimDownSights.Removal"))))
	{
		MontageToPlay = FireIronsightsMontage;
	}

	// Play fire montage and wait for event telling us to spawn the projectile
	USBAT_PlayMontageAndWaitForEvent* Task = USBAT_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this, NAME_None, MontageToPlay, FGameplayTagContainer(), 1.0f, NAME_None, false, 1.0f);
	Task->OnBlendOut.AddDynamic(this, &USBelicaGA_Fire::OnCompleted);
	Task->OnCompleted.AddDynamic(this, &USBelicaGA_Fire::OnCompleted);
	Task->OnInterrupted.AddDynamic(this, &USBelicaGA_Fire::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &USBelicaGA_Fire::OnCancelled);
	Task->EventReceived.AddDynamic(this, &USBelicaGA_Fire::EventReceived);
	// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
	Task->ReadyForActivation();

	FGameplayTagContainer OwnedTags;
	GetAbilitySystemComponentFromActorInfo()->GetOwnedGameplayTags(OwnedTags);

	// 가지고 있는 모든 태그 출력
	for (const FGameplayTag& Tag : OwnedTags)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has GameplayTag: %s"), *Tag.ToString());
	}
}

void USBelicaGA_Fire::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void USBelicaGA_Fire::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void USBelicaGA_Fire::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	// Montage told us to end the ability before the montage finished playing.
	// Montage was set to continue playing animation even after ability ends so this is okay.
	if (EventTag == FGameplayTag::RequestGameplayTag(FName("Event.Montage.EndAbility")))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	// Only spawn projectiles on the Server.
	// Predicting projectiles is an advanced topic not covered in this example.
	if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority && EventTag == FGameplayTag::RequestGameplayTag(FName("Event.Montage.SpawnProjectile")))
	{
		ASBelicaPlayerCharacter* Hero = Cast<ASBelicaPlayerCharacter>(GetAvatarActorFromActorInfo());
		if (!Hero)
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
		// todo: 손 위치로 바꿔야됌
		// Muzzle_02 왼쪽 손
		// Muzzle_01 오른쪽 손
		FVector Start = Hero->GetMesh()->GetSocketLocation(FName("Muzzle_01"));
		FTransform MuzzleTransform = Hero->GetMesh()->GetSocketTransform(FName("Muzzle_01"));
		int combo = Hero->GetComboCount();
		switch (combo)
		{
		case 0:
			Start = Hero->GetMesh()->GetSocketLocation(FName("Muzzle_01"));
			MuzzleTransform = Hero->GetMesh()->GetSocketTransform(FName("Muzzle_01"));
			Hero->SetComboCount(1);
			break;
		case 1:
			Start = Hero->GetMesh()->GetSocketLocation(FName("Muzzle_02"));
			MuzzleTransform = Hero->GetMesh()->GetSocketTransform(FName("Muzzle_02"));
			Hero->SetComboCount(2);
			break;
		case 2:
			Start = Hero->GetMesh()->GetSocketLocation(FName("Muzzle_01"));
			MuzzleTransform = Hero->GetMesh()->GetSocketTransform(FName("Muzzle_01"));
			Hero->SetComboCount(0);
			break;
		default:
			break;
		}
		FVector End = Hero->GetCameraBoom()->GetComponentLocation() + Hero->GetFollowCamera()->GetForwardVector() * Range;
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel());

		// Pass the damage to the Damage Execution Calculation through a SetByCaller value on the GameplayEffectSpec
		DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage);
		

		MuzzleTransform.SetRotation(Rotation.Quaternion());
		MuzzleTransform.SetScale3D(FVector(1.0f));

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ASBProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASBProjectile>(ProjectileClass, MuzzleTransform, GetOwningActorFromActorInfo(),
			Hero, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;
		Projectile->Range = Range;
		Projectile->FinishSpawning(MuzzleTransform);

	}
}
