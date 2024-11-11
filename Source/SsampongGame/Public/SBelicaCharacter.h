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






	// ���Ӿ����Ƽ�ý���
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class USAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UBasicAttributeSet> BasicAttributeSet;

	// Ư���±װ� �ִٸ� �ɷ� Ȱ��ȭ�� �� �ְ� ��
	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Demo|character")
	FText characterName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Animation")
	UAnimMontage* DeathMontage;

	// �����Ƽ ��ϵ�
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities")
	TMap<TSubclassOf<class UCharacterGameplayAbility>, UInputAction*> InputandAbilities;

	// ���� Ȱ��ȭ�� �����Ƽ
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities")
	TMap<TSubclassOf<UCharacterGameplayAbility>, FGameplayAbilitySpecHandle> ActivateAbilities;

	// ����Ʈ �����Ƽ
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities")
	TMap<TSubclassOf<UCharacterGameplayAbility>, UInputAction*> CharacterAbilities;

	// ĳ���Ͱ� �����ǰų� �������� �� �ʱ�ȭ�Ǵ� �⺻ �Ӽ����Դϴ�.
	// �̰��� ��� ����Ǵ� GE(Gameplay Effect)��, ����/������ �� �缳���Ǵ� �Ӽ� ���� ����ϴ�.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities") // �ϳ��� ����
	TSubclassOf<class UGameplayEffect> DefaulutAttributes;

	// ���� ȿ���� ����
	// �� ���� ���� ��
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Abilities") // �پ��� ȿ�� ������ �־��ֱ� ���� �ð� ���� �ִϸ��̼�
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	// ����Ʈ �����Ƽ �߰�
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
