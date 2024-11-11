 
#pragma once

#include "CoreMinimal.h"
#include "SBelicaCharacter.h"
#include "SBelicaPlayerState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "SBelicaPlayerCharacter.generated.h"

class USBFloatbarComponent;
class USBInteractionComponent;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API ASBelicaPlayerCharacter : public ASBelicaCharacter
{
	GENERATED_BODY()
public:
	

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	

	class USpringArmComponent* GetCameraBoom();

	UCameraComponent* GetFollowCamera();

	class USBelicaFloatingStatusBarWidget* GetFloatingStatusBar();

	UFUNCTION(BlueprintCallable, Category = "Demo|Camera")
	float GetStartingCameraBoomArmLength();
	UFUNCTION(BlueprintCallable, Category = "Demo|Camera")
	FVector GetStartingCameraBoomLocation();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combo")
	int ComboCount = 1;

	void SetComboCount(int count) { ComboCount = count; }
	int GetComboCount() { return ComboCount; }

	UFUNCTION(BlueprintCallable)
	void Interact_OnlyUI();
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Demo|Camera")
	float BaseTurnRate = 45.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Demo|Camera")
	float BaseLookuprate = 45.f;

	UPROPERTY(BlueprintReadOnly, Category = "Demo|Camera")
	float StartingCameraBoomArmLength;



	UPROPERTY(BlueprintReadOnly, Category = "Demo|Camera")
	FVector StartingCameraBoomLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category = "Demo|Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Demo|Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USBInteractionComponent> InteractionComp;

	USBFloatbarComponent* FloatbarComponent;
	/*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GASDocumentation|UI")
	TSubclassOf<class USBelicaFloatingStatusBarWidget> UIFloatingStatusBarClass;

	UPROPERTY()
	class USBelicaFloatingStatusBarWidget* UIFloatingStatusBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GASDocumentation|UI")
	class UWidgetComponent* UIFloatingStatusBarComponent;*/


	// 향상된 입력 ------
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* SlashContext;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ConfirmAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* InteractAction;


	// -----

	bool ASCInputBound = false;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& _ActionValue);
	void Look(const FInputActionValue& _ActionValue);
	void Confirm(const FInputActionValue& _ActionValue);
	void Interact(const FInputActionValue& _ActionValue);


	virtual void OnRep_PlayerState() override;

	void BindASCInput();

	ASBelicaPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

	void InitializeStartingValues(ASBelicaPlayerState* PS1);

	UFUNCTION()
	void InitializeFloatingStatusBar();
};
