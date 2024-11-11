// Fill out your copyright notice in the Description page of Project Settings.


#include "Charcters/Abilities/SBelicaMovementComponent.h"

#include "AbilitySystemComponent.h"
#include "SBelicaCharacter.h"



USBelicaMovementComponent::USBelicaMovementComponent()
{
	SprintSpeedMultiplier = 1.6f;
	ADSSpeedMultiplier = 0.5f;
}

float USBelicaMovementComponent::GetMaxSpeed() const
{
	ASBelicaCharacter* Owner = Cast<ASBelicaCharacter>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Owner"), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	if (!Owner->IsAlive())
	{
		return 0.0f;
	}

	if (Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun"))))
	{
		return 0.0f;
	}

	if (RequestToStartSprinting)
	{
		return Owner->GetSpeed() * SprintSpeedMultiplier;
	}

	if (RequestToStartADS)
	{
		return Owner->GetSpeed() * ADSSpeedMultiplier;
	}

	return Owner->GetSpeed();
}

void USBelicaMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	RequestToStartSprinting = (Flags & FSavedMove_Character::FLAG_Custom_0) != 0;

	RequestToStartADS = (Flags & FSavedMove_Character::FLAG_Custom_1) != 0;
}

FNetworkPredictionData_Client* USBelicaMovementComponent::GetPredictionData_Client() const
{
	check(PawnOwner != NULL);

	if (!ClientPredictionData)
	{
		USBelicaMovementComponent* MutableThis = const_cast<USBelicaMovementComponent*>(this);

		MutableThis->ClientPredictionData = new FGDNetworkPredictionData_Client(*this);
		MutableThis->ClientPredictionData->MaxSmoothNetUpdateDist = 92.f;
		MutableThis->ClientPredictionData->NoSmoothNetUpdateDist = 140.f;
	}

	return ClientPredictionData;
}

void USBelicaMovementComponent::StartSprinting()
{
	RequestToStartSprinting = true;
}

void USBelicaMovementComponent::StopSprinting()
{
	RequestToStartSprinting = false;
}

void USBelicaMovementComponent::StartAimDownSights()
{
	RequestToStartADS = true;
}

void USBelicaMovementComponent::StopAimDownSights()
{
	RequestToStartADS = false;
}

void USBelicaMovementComponent::FGDSavedMove::Clear()
{
	Super::Clear();


	SavedRequestToStartSprinting = false;
	SavedRequestToStartADS = false;
}

uint8 USBelicaMovementComponent::FGDSavedMove::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	if (SavedRequestToStartSprinting)
	{
		Result |= FLAG_Custom_0;
	}

	if (SavedRequestToStartADS)
	{
		Result |= FLAG_Custom_1;
	}

	return Result;
}

bool USBelicaMovementComponent::FGDSavedMove::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character,
	float MaxDelta) const
{
	//Set which moves can be combined together. This will depend on the bit flags that are used.
	if (SavedRequestToStartSprinting != ((FGDSavedMove*)&NewMove)->SavedRequestToStartSprinting)
	{
		return false;
	}

	if (SavedRequestToStartADS != ((FGDSavedMove*)&NewMove)->SavedRequestToStartADS)
	{
		return false;
	}

	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void USBelicaMovementComponent::FGDSavedMove::SetMoveFor(ACharacter* Character, float InDeltaTime,
	FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);

	USBelicaMovementComponent* CharacterMovement = Cast<USBelicaMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
		SavedRequestToStartSprinting = CharacterMovement->RequestToStartSprinting;
		SavedRequestToStartADS = CharacterMovement->RequestToStartADS;
	}
}

void USBelicaMovementComponent::FGDSavedMove::PrepMoveFor(ACharacter* Character)
{
	Super::PrepMoveFor(Character);

	USBelicaMovementComponent* CharacterMovement = Cast<USBelicaMovementComponent>(Character->GetCharacterMovement());
	if (CharacterMovement)
	{
	}
}

USBelicaMovementComponent::FGDNetworkPredictionData_Client::FGDNetworkPredictionData_Client(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{
}

FSavedMovePtr USBelicaMovementComponent::FGDNetworkPredictionData_Client::AllocateNewMove()
{
	return FSavedMovePtr(new FGDSavedMove());
}
