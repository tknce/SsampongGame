

#include "Charcters/Component/SBFloatbarComponent.h"

#include "SBelicaPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SBelicaFloatingStatusBarWidget.h"
#include <AbilitySystemComponent.h>

#include "Charcters/SBelicaPlayerCharacter.h"

USBFloatbarComponent::USBFloatbarComponent()
{
	UIFloatingStatusBarComponent = CreateDefaultSubobject<UWidgetComponent>(FName("UIFloatingStatusBarComponent"));
}


USBelicaFloatingStatusBarWidget* USBFloatbarComponent::GetFloatingStatusBar()
{
	return UIFloatingStatusBar;
}

void USBFloatbarComponent::InitializeFloatingStatusBar()
{
	ASBelicaCharacter* Owner = Cast<ASBelicaCharacter>(GetOwner());
	if (UIFloatingStatusBar || !IsValid(Owner->GetAbilitySystemComponent()))
	{
		return;
	}

	UIFloatingStatusBarClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/BruePrint/UI/SBelicaFloatingStatusBarWidget_player.SBelicaFloatingStatusBarWidget_player_C"));
	if (!UIFloatingStatusBarClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Failed to find UIFloatingStatusBarClass. If it was moved, please update the reference location in C++."), *FString(__FUNCTION__));
	}
	// Setup UI for Locally Owned Players only, not AI or the server's copy of the PlayerControllers
	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->IsLocalPlayerController())
	{
		if (UIFloatingStatusBarClass)
		{
			UIFloatingStatusBar = CreateWidget<USBelicaFloatingStatusBarWidget>(PC, UIFloatingStatusBarClass);
			if (UIFloatingStatusBar && UIFloatingStatusBarComponent)
			{
				UIFloatingStatusBarComponent->SetWidget(UIFloatingStatusBar);

				// Setup the floating status bar
				UIFloatingStatusBar->SetHealthPercentage(Owner->GetHealth() / Owner->GetMaxHealth());
				UIFloatingStatusBar->SetManaPercentage(Owner->GetMana() / Owner->GetMaxMana());
			}
		}
	}
}


void USBFloatbarComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwner()->GetRootComponent())
	{
		UIFloatingStatusBarComponent->SetupAttachment(GetOwner()->GetRootComponent());
		UIFloatingStatusBarComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		UIFloatingStatusBarComponent->SetRelativeLocation(FVector(0, 0, 120));
		UIFloatingStatusBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		UIFloatingStatusBarComponent->SetDrawSize(FVector2D(500, 500));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UIFloatingStatusBarComponent create fail."));
	}


}