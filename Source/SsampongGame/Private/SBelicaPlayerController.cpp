// Fill out your copyright notice in the Description page of Project Settings.


#include "SBelicaPlayerController.h"

#include "SBelicaPlayerState.h"
//#include <Subsystems/PanelExtensionSubsystem.h>
#include "SHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "SBelicaPlayerState.h"


void ASBelicaPlayerController::CreateHUD()
{
	// Only create once
	if (UIHUDWidget)
	{
		return;
	}

	// Only create a HUD for local player
	if (!IsLocalPlayerController())
	{
		return;
	}

	ASBelicaPlayerState* PS = GetPlayerState<ASBelicaPlayerState>();
	if (!PS)
	{
		return;
	}

	UIHUDWidget = CreateWidget<USHUDWidget>(this, UIHUDWidgetClass);
	UIHUDWidget->AddToViewport();

	UIHUDWidget->SetCurrentHealth(PS->GetHealth());
	UIHUDWidget->SetMaxHealth(PS->GetMaxHealth());
	UIHUDWidget->SetHealthPercentage(PS->GetHealth() / FMath::Max<float>(PS->GetMaxHealth(), 1.f));
	UIHUDWidget->SetCurrentMana(PS->GetMana());
	UIHUDWidget->SetMaxMana(PS->GetMaxMana());
	UIHUDWidget->SetManaPercentage(PS->GetMana()/ FMath::Max<float>(PS->GetMaxMana(), 1.f));

}

void ASBelicaPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ASBelicaPlayerState* PS = GetPlayerState<ASBelicaPlayerState>();
	if(PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

USHUDWidget* ASBelicaPlayerController::GetHUD()
{
	return UIHUDWidget;
}

void ASBelicaPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CreateHUD();
}

// 이후는 UI만들떄나 쓴다.
