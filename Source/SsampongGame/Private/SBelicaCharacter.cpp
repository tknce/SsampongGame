#include "SBelicaCharacter.h"
#include "SBelicaPlayerState.h"

#include "Components/CapsuleComponent.h"
#include "BasicAttributeSet.h"
#include "Charcters/Abilities/SAbilitySystemComponent.h"
#include "Charcters/Abilities/CharacterGameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <EnhancedInputComponent.h>
#include "GameplayAbilitySpecHandle.h"


#include "Charcters/Abilities/SBelicaMovementComponent.h"


ASBelicaCharacter::ASBelicaCharacter()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);

}

ASBelicaCharacter::ASBelicaCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USBelicaMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);

	bAlwaysRelevant = true;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));

	AbilitySystemComponent = CreateDefaultSubobject<USAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributeSet"));
}

bool ASBelicaCharacter::IsAlive() const
{
	return GetHealth() > 0.f;
}

// 
int32 ASBelicaCharacter::GetAbilityLevel(DemoAbilityID AbilityID) const
{
	return 1;
}


void ASBelicaCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}
	AbilitySystemComponent->SetEnhancedInputComponent(CastChecked<UEnhancedInputComponent>(Owner->InputComponent));

	for (auto [StartupAbility, input] : CharacterAbilities)
	{
		if (ActivateAbilities.Contains(StartupAbility)) continue;
		FGameplayAbilitySpecHandle Handle;
		if (StartupAbility)
			Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));

		if (input)
		{
			AbilitySystemComponent->SetInputBinding(input, Handle);
		}
	}
	AbilitySystemComponent->CharacterAbilitiesGiven = true;

}

void ASBelicaCharacter::RemoveCharacterAbilities()
{

	if(GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid( ) || !AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}
	TArray<FGameplayAbilitySpecHandle> AbilitesToRemove;
	for(const auto& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitesToRemove.Add(Spec.Handle);
		}
	}

	for(int32 i = 0; i < AbilitesToRemove.Num(); ++i)
	{
		AbilitySystemComponent->ClearAbility(AbilitesToRemove[i]);
	}

	ActivateAbilities.Empty();	
	AbilitySystemComponent->CharacterAbilitiesGiven = false;
}

void ASBelicaCharacter::InputButtonAddAbility(DemoAbilityID Input)
{
	// InputandAbilities
	for (auto [ability, inputAction] : InputandAbilities)
	{
		if (ActivateAbilities.Contains(ability)) continue;
		if (ability.GetDefaultObject()->AbilityID != Input) continue;

		FGameplayAbilitySpecHandle Handle;
		FGameplayAbilitySpec spec;
		spec = FGameplayAbilitySpec(ability, GetAbilityLevel(ability.GetDefaultObject()->AbilityID),
		                            static_cast<int32>(ability.GetDefaultObject()->AbilityInputID), this);
		if (ability)
			Handle = AbilitySystemComponent->GiveAbility(spec);
		
		if (inputAction)
		{
			AbilitySystemComponent->SetInputBinding(inputAction, Handle);
		}
		ActivateAbilities.Add(ability, Handle);
	}
}


void ASBelicaCharacter::Die()
{
	RemoveCharacterAbilities();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectsTagsRemove;
		EffectsTagsRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsEremoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectsTagsRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
		// GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);
		//AbilitySystemComponent->PlayMontageSimulated(DeathMontage, 1.f);
		bDead = true;
	}			
	else FinishDying();
}

void ASBelicaCharacter::FinishDying()
{
	Destroy();
}

float ASBelicaCharacter::GetCharacterLevel() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetLevel();

	return 0.0f;
}

float ASBelicaCharacter::GetHealth() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetHealth();

	return 0.0f;
}

float ASBelicaCharacter::GetMaxHealth() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetMaxHealth();
	return 0.0f;
}

float ASBelicaCharacter::GetMana() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetMana();
	return 0.0f;
}

float ASBelicaCharacter::GetMaxMana() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetMaxMana();
	return 0.0f;
}

float ASBelicaCharacter::GetMagicAttack() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetMagicAttack();
	return 0.0f;
}

float ASBelicaCharacter::GetMaxMagicAttack() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetMaxMagicAttack();
	return 0.0f;
}

float ASBelicaCharacter::GetDefense() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetDefense();
	return 0.0f;
}

float ASBelicaCharacter::GetSpeed() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetSpeed();
	return 0.0f;
}

float ASBelicaCharacter::GetMaxSpeed() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetMaxSpeed();
	return 0.0f;
}

float ASBelicaCharacter::GetAttackSpeed() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetAttackSpeed();
	return 0.0f;
}

float ASBelicaCharacter::GetMaxAttackSpeed() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetMaxAttackSpeed();
	return 0.0f;
}

float ASBelicaCharacter::GetCooldownAcceleration() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetCooldownAcceleration();
	return 0.0f;
}

float ASBelicaCharacter::GetMaxCooldownAcceleration() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetMaxCooldownAcceleration();
	return 0.0f;
}

float ASBelicaCharacter::GetCooldown() const
{
	if (BasicAttributeSet.IsValid())
		return BasicAttributeSet->GetCooldown();
	return 0.0f;
}

void ASBelicaCharacter::AddCharacterAbilities_Enemy()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}
	for (auto [StartupAbility, input] : CharacterAbilities)
	{
		if (ActivateAbilities.Contains(StartupAbility)) continue;
		FGameplayAbilitySpecHandle Handle;
		if (StartupAbility)
			Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));

		if (input)
		{
			AbilitySystemComponent->SetInputBinding(input, Handle);
		}
		ActivateAbilities.Add(StartupAbility, Handle);
	}
	//AbilitySystemComponent->CharacterAbilitiesGiven = true;
	//for (auto[ StartupAbility, input] : CharacterAbilities)
	//{
	//	AbilitySystemComponent->GiveAbility(
	//		FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	//}

	AbilitySystemComponent->CharacterAbilitiesGiven = true;
}

void ASBelicaCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid()) return;

	if (!DefaulutAttributes) { UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's blueprint"), *FString(__FUNCTION__), *GetName());  return; }

	// ȿ���� �ùٸ��� �ϴ°� ��ȿüũ
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	// ������ �Ѱ��� ��ȿ���� üũ
	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaulutAttributes, GetCharacterLevel(),EffectContext);
	if(NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}

}

void ASBelicaCharacter::AddStartupEffects()
{
	//
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->StartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for(auto GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}		
	}

	AbilitySystemComponent->StartupEffectsApplied = true;	
}

void ASBelicaCharacter::SetHealth(float hp)
{
	if(BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetHealth(hp);
	}
}

void ASBelicaCharacter::SetMaxHealth(float hp)
{
	if (BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetMaxHealth(BasicAttributeSet->GetMaxHealth() + hp);
	}
}

void ASBelicaCharacter::SetMaxMana(float mp)
{
	if (BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetMaxMana(BasicAttributeSet->GetMaxMana() + mp);
	}
}

void ASBelicaCharacter::SetMana(float mp)
{
	if (BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetMana(mp);
	}
}

void ASBelicaCharacter::SetMagicAttack(float ma)
{
	if (BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetMana(ma);
	}
}

void ASBelicaCharacter::SetDefense(float df)
{
	if (BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetMana(df);
	}
}

void ASBelicaCharacter::SetSpeed(float sp)
{
	if (BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetMana(sp);
	}
}

void ASBelicaCharacter::SetAttackSpeed(float as)
{
	if (BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetMana(as);
	}
}

void ASBelicaCharacter::SetCooldownAcceleration(float ada)
{
	if (BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetMana(ada);
	}
}

void ASBelicaCharacter::SetCooldown(float ct)
{
	if (BasicAttributeSet.IsValid())
	{
		BasicAttributeSet->SetMana(ct);
	}
}


UAbilitySystemComponent* ASBelicaCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

