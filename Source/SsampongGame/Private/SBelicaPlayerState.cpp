// Fill out your copyright notice in the Description page of Project Settings.


#include "SBelicaPlayerState.h"
#include "Charcters/Abilities/SAbilitySystemComponent.h"
#include "Charcters/SBelicaPlayerCharacter.h"
#include "BasicAttributeSet.h"
#include "SBelicaPlayerController.h"
#include "SHUDWidget.h"
#include "UI/SBelicaFloatingStatusBarWidget.h"

ASBelicaPlayerState::ASBelicaPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<USAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* ASBelicaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBasicAttributeSet* ASBelicaPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool ASBelicaPlayerState::IsAlive() const
{
	return GetHealth() > 0.f;
}

void ASBelicaPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	// HUD구현할때함
	ASBelicaPlayerController* PC = Cast<ASBelicaPlayerController>(GetOwner());
	if (PC)
	{
		USHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->ShowAbilityConfirmCancelText(ShowText);
		}
	}
}

float ASBelicaPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float ASBelicaPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float ASBelicaPlayerState::GetMana() const
{
	return AttributeSetBase->GetMana();
}

float ASBelicaPlayerState::GetMaxMana() const
{
	return AttributeSetBase->GetMaxMana();
}

int32 ASBelicaPlayerState::GetCharacterLevel() const
{
	return AttributeSetBase->GetLevel();
}

float ASBelicaPlayerState::GetMagicAttack() const
{
	return AttributeSetBase->GetMagicAttack();
}

float ASBelicaPlayerState::GetMaxMagicAttack() const
{
	return AttributeSetBase->GetMaxMagicAttack();
}

float ASBelicaPlayerState::GetDefense() const
{
	return AttributeSetBase->GetDefense();
}

float ASBelicaPlayerState::GetSpeed() const
{
	return AttributeSetBase->GetSpeed();
}

float ASBelicaPlayerState::GetMaxSpeed() const
{
	return AttributeSetBase->GetMaxSpeed();
}

float ASBelicaPlayerState::GetAttackSpeed() const
{
	return AttributeSetBase->GetAttackSpeed();
}

float ASBelicaPlayerState::GetMaxAttackSpeed() const
{
	return AttributeSetBase->GetMaxAttackSpeed();
}

float ASBelicaPlayerState::GetCooldownAcceleration() const
{
	return AttributeSetBase->GetCooldownAcceleration();
}

float ASBelicaPlayerState::GetMaxCooldownAcceleration() const
{
	return AttributeSetBase->GetMaxCooldownAcceleration();
}

float ASBelicaPlayerState::GetCooldown() const
{
	return AttributeSetBase->GetCooldown();
}

void ASBelicaPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		HealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate				(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &ASBelicaPlayerState::HealthChanged);
		MaxHealthChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate				(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &ASBelicaPlayerState::MaxHealthChanged);
		ManaChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate					(AttributeSetBase->GetManaAttribute()).AddUObject(this, &ASBelicaPlayerState::ManaChanged);
		MaxManaChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate				(AttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &ASBelicaPlayerState::MaxManaChanged);
		LevelChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate					(AttributeSetBase->GetLevelAttribute()).AddUObject(this, &ASBelicaPlayerState::CharacterLevelChanged);
		MagicAttackChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate			(AttributeSetBase->GetMagicAttackAttribute()).AddUObject(this, &ASBelicaPlayerState::MagicAttackChanged);
		MaxMagicAttackChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate		(AttributeSetBase->GetMaxMagicAttackAttribute()).AddUObject(this, &ASBelicaPlayerState::MaxMagicAttackChanged);
		DefenseChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate				(AttributeSetBase->GetDefenseAttribute()).AddUObject(this, &ASBelicaPlayerState::DefenseChanged);
		SpeedChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate					(AttributeSetBase->GetSpeedAttribute()).AddUObject(this, &ASBelicaPlayerState::SpeedChanged);
		MaxSpeedChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate				(AttributeSetBase->GetMaxSpeedAttribute()).AddUObject(this, &ASBelicaPlayerState::MaxSpeedChanged);
		AttackSpeedChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate			(AttributeSetBase->GetAttackSpeedAttribute()).AddUObject(this, &ASBelicaPlayerState::AttackSpeedChanged);
		MaxAttackSpeedChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate		(AttributeSetBase->GetMaxAttackSpeedAttribute()).AddUObject(this, &ASBelicaPlayerState::MaxAttackSpeedChanged);
		CooldownAccelerationChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate	(AttributeSetBase->GetCooldownAccelerationAttribute()).AddUObject(this, &ASBelicaPlayerState::CooldownAccelerationChanged);
		MaxCooldownAccelerationChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxCooldownAccelerationAttribute()).AddUObject(this, &ASBelicaPlayerState::MaxCooldownAccelerationChanged);
		CooldownChangeDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate				(AttributeSetBase->GetCooldownAttribute()).AddUObject(this, &ASBelicaPlayerState::CooldownChanged);



		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ASBelicaPlayerState::StunTagChanged);
	}
}


void ASBelicaPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Health Changed!"));

	float Health = Data.NewValue;

	ASBelicaPlayerCharacter* Hero = Cast<ASBelicaPlayerCharacter>(GetPawn());
	if (Hero)
	{
		USBelicaFloatingStatusBarWidget* BlicaFloatingStatusBar = Hero->GetFloatingStatusBar();
		if (BlicaFloatingStatusBar)
		{
			BlicaFloatingStatusBar->SetHealthPercentage(Health / GetMaxHealth());
		}
	}



	ASBelicaPlayerCharacter* Belica = Cast<ASBelicaPlayerCharacter>(GetPawn());

	if (Belica)
	{
		if (Health <= 0)
			Belica->Die();
	}
	/*ASBelicaPlayerController* PC = Cast<ASBelicaPlayerController>(GetOwner());
	if (PC)
	{
		USHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxHealth(MaxHealth);
		}
	}*/




	// 삭제예정
	ASBelicaPlayerController* PC = Cast<ASBelicaPlayerController>(GetOwner());
	if (PC)
	{
		USHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetCurrentHealth(Health);
		}
	}
}

void ASBelicaPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Health Changed!"));
	float MaxHealth = Data.NewValue;

	ASBelicaPlayerCharacter* Hero = Cast<ASBelicaPlayerCharacter>(GetPawn());
	if (Hero)
	{
		USBelicaFloatingStatusBarWidget* BlicaFloatingStatusBar = Hero->GetFloatingStatusBar();
		if (BlicaFloatingStatusBar)
		{
			BlicaFloatingStatusBar->SetHealthPercentage(GetMaxHealth() / MaxHealth);
		}
	}
	// Update the HUD
	ASBelicaPlayerController* PC = Cast<ASBelicaPlayerController>(GetOwner());
	if (PC)
	{
		USHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxHealth(MaxHealth);
		}
	}
}

void ASBelicaPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Mana Changed!"));

	float Mana = Data.NewValue;


	ASBelicaPlayerCharacter* Hero = Cast<ASBelicaPlayerCharacter>(GetPawn());
	if (Hero)
	{
		USBelicaFloatingStatusBarWidget* BlicaFloatingStatusBar = Hero->GetFloatingStatusBar();
		if (BlicaFloatingStatusBar)
		{
			BlicaFloatingStatusBar->SetManaPercentage(Mana / GetMaxHealth());
		}
	}

	ASBelicaPlayerController* PC = Cast<ASBelicaPlayerController>(GetOwner());
	if (PC)
	{
		USHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetCurrentMana(Mana);
		}
	}
}

void ASBelicaPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Mana Changed!"));

	float maxMana = Data.NewValue;



	ASBelicaPlayerCharacter* Hero = Cast<ASBelicaPlayerCharacter>(GetPawn());
	if (Hero)
	{
		USBelicaFloatingStatusBarWidget* BlicaFloatingStatusBar = Hero->GetFloatingStatusBar();
		if (BlicaFloatingStatusBar)
		{
			BlicaFloatingStatusBar->SetManaPercentage(GetMaxHealth() / maxMana);
		}
	}

	ASBelicaPlayerController* PC = Cast<ASBelicaPlayerController>(GetOwner());
	if (PC)
	{
		USHUDWidget* HUD = PC->GetHUD();
		if (HUD)
		{
			HUD->SetMaxMana(maxMana);
		}
	}
}

void ASBelicaPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Character Level Changed!"));
}

void ASBelicaPlayerState::MagicAttackChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::MaxMagicAttackChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::DefenseChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::SpeedChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::MaxSpeedChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::AttackSpeedChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::MaxAttackSpeedChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::CooldownAccelerationChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::MaxCooldownAccelerationChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::CooldownChanged(const FOnAttributeChangeData& Data)
{
}

void ASBelicaPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 newCount)
{
	if (newCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag((FName("Ability"))));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag((FName("Ability,NotAenceledByStun"))));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);

	}
}
