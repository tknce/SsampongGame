


#include "Charcters/SBelicaPlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AI/PlayerAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components\\InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "SBelicaPlayerState.h"
#include "Charcters/Abilities/SAbilitySystemComponent.h"
#include "SBelicaPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/SBelicaFloatingStatusBarWidget.h"
#include <Kismet/GameplayStatics.h>

#include "Charcters/Component/SBFloatbarComponent.h"
#include "Charcters/Component/SBInteractionComponent.h"

ASBelicaPlayerCharacter::ASBelicaPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 70.f));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.f;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	InteractionComp = CreateDefaultSubobject<USBInteractionComponent>("InteractionComp");


	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	FloatbarComponent = CreateDefaultSubobject<USBFloatbarComponent>("FloatbarComponent");

	/*UIFloatingStatusBarComponent = CreateDefaultSubobject<UWidgetComponent>(FName("UIFloatingStatusBarComponent"));
	UIFloatingStatusBarComponent->SetupAttachment(RootComponent);
	UIFloatingStatusBarComponent->SetRelativeLocation(FVector(0, 0, 120));
	UIFloatingStatusBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	UIFloatingStatusBarComponent->SetDrawSize(FVector2D(500, 500));

	UIFloatingStatusBarClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/BruePrint/UI/SBelicaFloatingStatusBarWidget_player.SBelicaFloatingStatusBarWidget_player_C"));
	if (!UIFloatingStatusBarClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Failed to find UIFloatingStatusBarClass. If it was moved, please update the reference location in C++."), *FString(__FUNCTION__));
	}*/


	AIControllerClass = APlayerAIController::StaticClass();

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void ASBelicaPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)

{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASBelicaPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASBelicaPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASBelicaPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Triggered, this, &ASBelicaPlayerCharacter::Confirm);
		//EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ASBelicaPlayerCharacter::Interact);
	}

	BindASCInput();
}


USpringArmComponent* ASBelicaPlayerCharacter::GetCameraBoom()
{
	return CameraBoom;
}

UCameraComponent* ASBelicaPlayerCharacter::GetFollowCamera()
{
	return FollowCamera;
}

USBelicaFloatingStatusBarWidget* ASBelicaPlayerCharacter::GetFloatingStatusBar()
{
	return FloatbarComponent->GetFloatingStatusBar();
}

float ASBelicaPlayerCharacter::GetStartingCameraBoomArmLength()
{
	return StartingCameraBoomArmLength;
}

FVector ASBelicaPlayerCharacter::GetStartingCameraBoomLocation()
{
	return StartingCameraBoomLocation;
}

void ASBelicaPlayerCharacter::Interact_OnlyUI()
{
	InteractionComp->PrimaryInteract();
}

void ASBelicaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		Subsystem->AddMappingContext(SlashContext, 0);
	}
}

void ASBelicaPlayerCharacter::Move(const FInputActionValue& _ActionValue)
{
	const FVector2D MovementVector = _ActionValue.Get<FVector2D>();

	if(MovementVector.Y)
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), MovementVector.Y);
	// D A
	if(MovementVector.X)
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)), MovementVector.X);
}

void ASBelicaPlayerCharacter::Look(const FInputActionValue& _ActionValue)
{
	const FVector2D LookAxisVector = _ActionValue.Get<FVector2D>();
	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void ASBelicaPlayerCharacter::Confirm(const FInputActionValue& _ActionValue)
{
	if(HasAuthority())
	{
		AbilitySystemComponent->TargetConfirm();
	}	
}

void ASBelicaPlayerCharacter::Interact(const FInputActionValue& _ActionValue)
{
	InteractionComp->PrimaryInteract();
}


void ASBelicaPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ASBelicaPlayerState* PS1 = GetPlayerState<ASBelicaPlayerState>();
	if (PS1)
	{
		InitializeStartingValues(PS1);
		BindASCInput();
		InitializeAttributes();
	}
}

void ASBelicaPlayerCharacter::BindASCInput()
{
	if (!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(
			FString("confirmTarget"),
			FString("CancelTarget"),
			FString("DemoAbilityID"),
			static_cast<int32>(DemoAbilityID::Cancel)));

		ASCInputBound = true;
	}
}


void ASBelicaPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ASBelicaPlayerState* PS1 = GetPlayerState<ASBelicaPlayerState>();
	if (PS1)
	{
		InitializeStartingValues(PS1);

		AddStartupEffects();
		AddCharacterAbilities();

		ASBelicaPlayerController* PC = Cast<ASBelicaPlayerController>(GetController());
		if (PC)
		{
			PC->CreateHUD();
		}

		InitializeFloatingStatusBar();
	}
}

void ASBelicaPlayerCharacter::InitializeStartingValues(ASBelicaPlayerState* PS1)
{

	AbilitySystemComponent = Cast<USAbilitySystemComponent>(PS1->GetAbilitySystemComponent());

	PS1->GetAbilitySystemComponent()->InitAbilityActorInfo(PS1, this);

	BasicAttributeSet = PS1->GetAttributeSetBase();

	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);
	InitializeAttributes();

	SetHealth(GetMaxHealth());
	SetMana(GetMaxMana());


}

void ASBelicaPlayerCharacter::InitializeFloatingStatusBar()
{
	// Only create once
	FloatbarComponent->InitializeFloatingStatusBar();
}
