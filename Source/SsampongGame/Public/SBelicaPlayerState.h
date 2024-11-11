// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BasicAttributeSet.h"
#include "SBelicaPlayerState.generated.h"


class USAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API ASBelicaPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ASBelicaPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UBasicAttributeSet* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable,Category = "Demo|BelicaPlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|UI")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetMagicAttack() const;
	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetMaxMagicAttack() const;
	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetDefense() const;
	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetMaxSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetAttackSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetMaxAttackSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetCooldownAcceleration() const;
	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetMaxCooldownAcceleration() const;
	UFUNCTION(BlueprintCallable, Category = "Demo|BelicaPlayerState|Attributes")
	float GetCooldown() const;

protected:
	UPROPERTY()
	class USAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	class UBasicAttributeSet* AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;
	FDelegateHandle ManaChangeDelegateHandle;
	FDelegateHandle MaxManaChangeDelegateHandle;
	FDelegateHandle LevelChangeDelegateHandle;
	FDelegateHandle MagicAttackChangeDelegateHandle;
	FDelegateHandle	MaxMagicAttackChangeDelegateHandle;
	FDelegateHandle	DefenseChangeDelegateHandle;
	FDelegateHandle	SpeedChangeDelegateHandle;
	FDelegateHandle	MaxSpeedChangeDelegateHandle;
	FDelegateHandle	AttackSpeedChangeDelegateHandle;
	FDelegateHandle	MaxAttackSpeedChangeDelegateHandle;
	FDelegateHandle	CooldownAccelerationChangeDelegateHandle;
	FDelegateHandle	MaxCooldownAccelerationChangeDelegateHandle;
	FDelegateHandle	CooldownChangeDelegateHandle;

	virtual void BeginPlay() override;

	// ASB@todo 케릭터 위에 뜨는 위젯 업데이트 용 추후 추가 예정
	// 데미지 받을 때만 떨어지게 해놨는데 일단은 적용시켜놈
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void CharacterLevelChanged(const FOnAttributeChangeData& Data);
	virtual void MagicAttackChanged(const FOnAttributeChangeData& Data);
	virtual void MaxMagicAttackChanged(const FOnAttributeChangeData& Data);
	virtual void DefenseChanged(const FOnAttributeChangeData& Data);
	virtual void SpeedChanged(const FOnAttributeChangeData& Data);
	virtual void MaxSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void AttackSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void MaxAttackSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void CooldownAccelerationChanged(const FOnAttributeChangeData& Data);
	virtual void MaxCooldownAccelerationChanged(const FOnAttributeChangeData& Data);
	virtual void CooldownChanged(const FOnAttributeChangeData& Data);



	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 newCount);
};
