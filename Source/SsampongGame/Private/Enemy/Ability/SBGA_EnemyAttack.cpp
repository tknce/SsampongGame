// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Ability/SBGA_EnemyAttack.h"

#include "AbilitySystemComponent.h"
#include "SBelicaCharacter.h"
#include "Charcters/SBProjectile.h"
#include "Charcters/Abilities/AbilityTasks/SBAT_PlayMontageAndWaitForEvent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


USBGA_EnemyAttack::USBGA_EnemyAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Enemy.Skill.Attack"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Enemy.Skill")));
}

void USBGA_EnemyAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
	UAnimMontage* MontageToPlay = FireHipMontage;

	USBAT_PlayMontageAndWaitForEvent* Task = USBAT_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this, NAME_None, MontageToPlay, FGameplayTagContainer(), 1.0f, NAME_None, false, 1.0f);
	Task->OnBlendOut.AddDynamic(this, &USBGA_EnemyAttack::OnCompleted);
	Task->OnCompleted.AddDynamic(this, &USBGA_EnemyAttack::OnCompleted);
	Task->OnInterrupted.AddDynamic(this, &USBGA_EnemyAttack::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &USBGA_EnemyAttack::OnCancelled);
	Task->EventReceived.AddDynamic(this, &USBGA_EnemyAttack::EventReceived);
	// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
	Task->ReadyForActivation();
}

void USBGA_EnemyAttack::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	Super::OnCancelled(EventTag, EventData);
}

void USBGA_EnemyAttack::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	Super::OnCompleted(EventTag, EventData);
}

void USBGA_EnemyAttack::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	Super::EventReceived(EventTag, EventData);
	if (EventTag == FGameplayTag::RequestGameplayTag(FName("Event.Montage.EndAbility")) )
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}


	if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority && EventTag == FGameplayTag::RequestGameplayTag(FName("Event.Montage.SpawnProjectile")))
	{
		ASBelicaCharacter* Hero = Cast<ASBelicaCharacter>(GetAvatarActorFromActorInfo());
		FVector Start = Hero->GetMesh()->GetSocketLocation(FName("Muzzle_01"));
		FTransform MuzzleTransform = Hero->GetMesh()->GetSocketTransform(FName("Muzzle_01"));
		FVector End = FVector();




		// 소환 위치를 결정하는 부분
		float SpawnDistance = 50.0f; // 원하는 거리 (앞쪽으로 이동할 거리)
		FVector ForwardVector = MuzzleTransform.GetRotation().Vector(); // Muzzle 방향의 Forward Vector
		FVector SpawnLocation = Start + (ForwardVector * SpawnDistance);
		MuzzleTransform.SetLocation(SpawnLocation);

		// 현재 플레이어 컨트롤러 가져오기
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		// 플레이어 캐릭터를 컨트롤러에서 가져오기
		ACharacter* PlayerCharacter = PlayerController ? Cast<ACharacter>(PlayerController->GetPawn()) : nullptr;

		if (TargetActor)
			End = TargetActor->GetActorLocation();
		else
			End = PlayerCharacter->GetActorLocation();
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



void USBGA_EnemyAttack::SetTargetActor(ASBelicaCharacter* actor)
{
	TargetActor = actor;
}
