// Fill out your copyright notice in the Description page of Project Settings.


#include "Store/MainStore/SBMainStore.h"

#include "BasicAttributeSet.h"
#include "Charcters/Abilities/SAbilitySystemComponent.h"
#include "Charcters/Component/SBFloatbarComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/SBelicaFloatingStatusBarWidget.h"
#include "UI/SBStoreWidget.h"


ASBMainStore::ASBMainStore()
{

    UIStoreComponent = CreateDefaultSubobject<UWidgetComponent>(FName("UIStoreComponent"));
    UIStoreComponent->SetupAttachment(RootComponent);

    FloatbarComponent = CreateDefaultSubobject<USBFloatbarComponent>("FloatbarComponent");

    HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BasicAttributeSet->GetHealthAttribute()).AddUObject(this, &ASBMainStore::HealthChanged);
}

void ASBMainStore::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC && PC->IsLocalPlayerController())
    {
        if (UIStoreClass)
        {
            UIStore = CreateWidget<USBStoreWidget>(PC, UIStoreClass);
            if (UIStore && UIStoreComponent)
            {
                UIStoreComponent->SetWidget(UIStore);
                UIStore->SetVisibility(ESlateVisibility::Hidden);
                UIStore->bIsFocusable = true;
            }
        }
    }
    if (UIStore->IsInViewport())
    {
        UIStore->RemoveFromParent();        
    }
    FloatbarComponent->InitializeFloatingStatusBar();


    if (AbilitySystemComponent.IsValid())
    {

        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        SetHealth(100.f);
        InitializeAttributes();
        AddStartupEffects();
        AddCharacterAbilities_Enemy();
    }
}

void ASBMainStore::Interact_Implementation(APawn* InstigatorPawn)
{
	ISBInterface::Interact_Implementation(InstigatorPawn);
    ToggleUI();
}

void ASBMainStore::OnActorLoaded_Implementation()
{
	ISBInterface::OnActorLoaded_Implementation();
    ToggleUI();
}

void ASBMainStore::HealthChanged(const FOnAttributeChangeData& Data)
{
    float Health = Data.NewValue;

    // Update floating status bar
    if (FloatbarComponent)
    {
        
        FloatbarComponent->UIFloatingStatusBar->SetHealthPercentage(Health / GetMaxHealth());
    }

    if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
    {
        Die();
    }
}

void ASBMainStore::ToggleUI()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    if (UIStore)
    {
        if (UIStore->IsInViewport())
        {
            UIStore->RemoveFromParent();
            UIStore->SetVisibility(ESlateVisibility::Hidden);

            if (PlayerController)
            {
                // 캐릭터의 움직임을 다시 활성화
                PlayerController->SetIgnoreMoveInput(false);
                PlayerController->SetIgnoreLookInput(false);

                // 마우스 커서를 숨기고 다시 게임 모드로 전환
                PlayerController->bShowMouseCursor = false;
                PlayerController->SetInputMode(FInputModeGameOnly());
            }
        }
        else
        {
            UIStore->AddToViewport();
            UIStore->SetVisibility(ESlateVisibility::Visible);

            UIStore->SetIsFocusable(true);
            
            FInputModeGameAndUI InputMode;
            InputMode.SetWidgetToFocus(UIStore->TakeWidget());
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

            if (PlayerController)
            {
                // 마우스 커서 표시 및 UI와의 상호작용 활성화
                PlayerController->bShowMouseCursor = true;
                PlayerController->SetInputMode(FInputModeUIOnly());
            }
        }
    }
}
