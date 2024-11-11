#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AbilitySystemInterface.h"

#include "SCharacter.generated.h"

UCLASS()

class SSAMPONGGAME_API ASCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:	
	ASCharacter();

protected:	
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* SlashContext;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities)
	UAbilitySystemComponent* AbilitySystemComponent;





	virtual void BeginPlay() override;
public:	

	void Move(const FInputActionValue& _ActionValue);
	void Look(const FInputActionValue& _ActionValue);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 어빌리티 시스템
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;



private:

};
