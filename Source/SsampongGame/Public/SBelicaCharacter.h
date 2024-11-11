// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include <SsampongGame/SsampongGame.h>
#include "GameplayAbilitySpecHandle.h"
#include "SBelicaCharacter.generated.h"


struct FGameplayAbilitySpec;

class UInputAction;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ASBelicaCharacter*, Character);

UCLASS()
class SSAMPONGGAME_API ASBelicaCharacter : public ACharacter, public  IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASBelicaCharacter();
	ASBelicaCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable,Category = "Demo|Character")
	FCharacterDiedDelegate OnCharacterDied;

	UPROPERTY(BlueprintReadWrite)
	bool bDead = false;


	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "Demo|Character")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character")
	virtual int32 GetAbilityLevel(DemoAbilityID AbilityID) const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character")
	virtual void FinishDying();


	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetMagicAttack() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetMaxMagicAttack() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetDefense() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetMaxSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetAttackSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetMaxAttackSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetCooldownAcceleration() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetMaxCooldownAcceleration() const;

	UFUNCTION(BlueprintCallable, Category = "Demo|Character|Attributes")
	float GetCooldown() const;






	// 게임어빌리티시스템
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class USAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UBasicAttributeSet> BasicAttributeSet;

	// 특정태그가 있다면 능력 활성화할 수 있게 함
	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Demo|character")
	FText characterName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Animation")
	UAnimMontage* DeathMontage;

	// 어빌리티 목록들
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities")
	TMap<TSubclassOf<class UCharacterGameplayAbility>, UInputAction*> InputandAbilities;

	// 현재 활성화된 어빌리티
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities")
	TMap<TSubclassOf<UCharacterGameplayAbility>, FGameplayAbilitySpecHandle> ActivateAbilities;

	// 디폴트 어빌리티
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities")
	TMap<TSubclassOf<UCharacterGameplayAbility>, UInputAction*> CharacterAbilities;

	// 캐릭터가 스폰되거나 리스폰될 때 초기화되는 기본 속성들입니다.
	// 이것은 즉시 적용되는 GE(Gameplay Effect)로, 스폰/리스폰 시 재설정되는 속성 값을 덮어씁니다.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities") // 하나의 설정
	TSubclassOf<class UGameplayEffect> DefaulutAttributes;

	// 시작 효과들 정의
	// 한 번만 실행 됌
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities") // 다양한 효과 설정값 넣어주기 위해 시각 음향 애니메이션
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	// 디폴트 어빌리티 추가
	virtual void AddCharacterAbilities();
	virtual void AddCharacterAbilities_Enemy();

	void InputButtonAddAbility(DemoAbilityID Input);

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void SetHealth(float hp);

	virtual void SetMaxHealth(float hp);

	virtual void SetMana(float mp);

	virtual void SetMaxMana(float hp);

	virtual void SetMagicAttack(float ma);

	virtual void SetDefense(float df);

	virtual void SetSpeed(float sp);

	virtual void SetAttackSpeed(float as);

	virtual void SetCooldownAcceleration(float ada);

	virtual void SetCooldown(float ct);









	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;




//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
