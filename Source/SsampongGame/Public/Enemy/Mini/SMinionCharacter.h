// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBelicaCharacter.h"
#include "GameplayEffectTypes.h"
#include "SMinionCharacter.generated.h"

class ASBWeaponBase;
/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API ASMinionCharacter : public ASBelicaCharacter
{
	GENERATED_BODY()
public:
	ASMinionCharacter(const class FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	bool TryAttack(FGameplayTag& AtivateTag, ASBelicaCharacter* TargetActor);

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASBWeaponBase> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	ASBWeaponBase* Weapon;

protected:

	// Actual hard pointer to AbilitySystemComponent
	UPROPERTY()
	class USAbilitySystemComponent* HardRefAbilitySystemComponent;

	// Actual hard pointer to AttributeSetBase
	UPROPERTY()
	class UBasicAttributeSet* HardRefAttributeSetBase;

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GASDocumentation|UI")
	TSubclassOf<class USBelicaFloatingStatusBarWidget> UIFloatingStatusBarClass;

	UPROPERTY()
	USBelicaFloatingStatusBarWidget* UIFloatingStatusBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GASDocumentation|UI")
	class UWidgetComponent* UIFloatingStatusBarComponent;

	FDelegateHandle HealthChangedDelegateHandle;

	virtual void PossessedBy(AController* NewController) override;

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);

	// Tag change callbacks
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
