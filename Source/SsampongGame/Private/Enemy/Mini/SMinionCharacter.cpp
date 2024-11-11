// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Mini/SMinionCharacter.h"

#include "AbilitySystemComponent.h"
#include "BasicAttributeSet.h"
#include "Charcters/Abilities/SAbilitySystemComponent.h"
#include "UI/SBelicaDamageTextWidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "UI/SBelicaFloatingStatusBarWidget.h"
#include <Kismet/GameplayStatics.h>

#include "AI/SBEnemyAIController.h"
#include "Charcters/Abilities/CharacterGameplayAbility.h"
#include "Enemy/Ability/SBGA_EnemyAttack.h"
#include "Item/SBWeaponBase.h"

ASMinionCharacter::ASMinionCharacter(const FObjectInitializer& ObjectInitializer)
{
	// Create ability system component, and set it to be explicitly replicated
	HardRefAbilitySystemComponent = CreateDefaultSubobject<USAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HardRefAbilitySystemComponent->SetIsReplicated(true);

	// Minimal Mode means that no GameplayEffects will replicate. They will only live on the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	HardRefAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	// Set our parent's TWeakObjectPtr
	AbilitySystemComponent = HardRefAbilitySystemComponent;

	// Create the attribute set, this replicates by default
// Adding it as a subobject of the owning actor of an AbilitySystemComponent
// automatically registers the AttributeSet with the AbilitySystemComponent
	HardRefAttributeSetBase = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("AttributeSetBase"));

	// Set our parent's TWeakObjectPtr
	BasicAttributeSet = HardRefAttributeSetBase;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	UIFloatingStatusBarComponent = CreateDefaultSubobject<UWidgetComponent>(FName("UIFloatingStatusBarComponent"));
	UIFloatingStatusBarComponent->SetupAttachment(RootComponent);
	UIFloatingStatusBarComponent->SetRelativeLocation(FVector(0, 0, 120));
	UIFloatingStatusBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	UIFloatingStatusBarComponent->SetDrawSize(FVector2D(500, 500));

	UIFloatingStatusBarClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/BruePrint/UI/SBelicaFloatingStatusBarWidget_enemy.SBelicaFloatingStatusBarWidget_enemy_C"));
	if (!UIFloatingStatusBarClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Failed to find UIFloatingStatusBarClass. If it was moved, please update the reference location in C++."), *FString(__FUNCTION__));
	}

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));

	AIControllerClass = ASBEnemyAIController::StaticClass();


	//AttachToComponent(SpawnedWeapon, FAttachmentTransformRules::KeepWorldTransform, FName("HammerSocket"));
	// E:/SsampongGame/Content/BruePrint/WeaponActor/BP_WeaponActor.uasset
	WeaponClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/BruePrint/WeaponActor/BP_WeaponActor.BP_WeaponActor_C"));

}

bool ASMinionCharacter::TryAttack(FGameplayTag& AtivateTag, ASBelicaCharacter* TargetActor)
{
	for (auto [ability, handle] : ActivateAbilities)
	{
		if(!ability->GetDefaultObject<UCharacterGameplayAbility>()->AbilityTags.HasTag(AtivateTag)) continue;

		if(AbilitySystemComponent->TryActivateAbility(handle))
		{
			AbilitySystemComponent->FindAbilitySpecFromHandle(handle);
			// ability->GetDefaultObject<USBGA_EnemyAttack>()->SetTargetActor(TargetActor);
			USBGA_EnemyAttack* a = Cast<USBGA_EnemyAttack>(AbilitySystemComponent->GetActivatableAbilities()[0].Ability);
			a->SetTargetActor(TargetActor);
			return true;
		}		
	}
	return false;
}

void ASMinionCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();
		AddStartupEffects();
		AddCharacterAbilities_Enemy();

		// SetHealth(GetMaxHealth());
		// Setup FloatingStatusBar UI for Locally Owned Players only, not AI or the server's copy of the PlayerControllers
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC && PC->IsLocalPlayerController())
		{
			if (UIFloatingStatusBarClass)
			{
				UIFloatingStatusBar = CreateWidget<USBelicaFloatingStatusBarWidget>(PC, UIFloatingStatusBarClass);
				if (UIFloatingStatusBar && UIFloatingStatusBarComponent)
				{
					UIFloatingStatusBarComponent->SetWidget(UIFloatingStatusBar);
					
					// Setup the floating status bar
					UIFloatingStatusBar->SetHealthPercentage(GetHealth() / GetMaxHealth());

					UIFloatingStatusBar->SetCharacterName(characterName);
				}
			}
		}

		// Attribute change callbacks
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BasicAttributeSet->GetHealthAttribute()).AddUObject(this, &ASMinionCharacter::HealthChanged);

		// Tag change callbacks
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ASMinionCharacter::StunTagChanged);

		SpawnDefaultController();
	}
}

void ASMinionCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ASMinionCharacter::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	// Update floating status bar
	if (UIFloatingStatusBar)
	{
		UIFloatingStatusBar->SetHealthPercentage(Health / GetMaxHealth());
	}

	if(!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		Die();
	}
}

void ASMinionCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}
