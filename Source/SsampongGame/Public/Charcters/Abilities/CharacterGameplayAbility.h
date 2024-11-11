// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SsampongGame/SsampongGame.h"
#include "CharacterGameplayAbility.generated.h"

/**
 * 
 */

UCLASS()
class SSAMPONGGAME_API UCharacterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UCharacterGameplayAbility();

	// �Է¿� �����Ͽ� Ư�� �ɷ��� �ڵ����� Ȱ��ȭ�մϴ�.
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Ability")
	DemoAbilityID AbilityInputID = DemoAbilityID::None;

	// ���԰� ���� : �Է°� �ڵ����� ������� �ʴ� �ɷ��� ���԰� �����ϱ� ���� ���Դϴ�.
	//�нú� �ɷ� : �нú� �ɷ��� �Է°� ������� �����Ƿ�, �ɷ��� ���԰� �Ϲ������� ������ �� �ִ� ����� �ʿ��մϴ�.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	DemoAbilityID AbilityID = DemoAbilityID::None;

	// �� ������ �ɷ��� �ο����ڸ��� �ڵ����� Ȱ��ȭ�ǵ��� �Ͽ�, �нú� �ɷ��̳� Ÿ�ο��� ������ ����Ǵ� �ɷ¿� �����մϴ�.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	// ������ ����ϸ� �ɷ��� �ο����ڸ��� �ڵ����� Ȱ��ȭ�Ǹ�, ������Ʈ�� �䱸�� ���� �ʱ�ȭ �۾��� ������ �� �ֽ��ϴ�.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
public:


};
