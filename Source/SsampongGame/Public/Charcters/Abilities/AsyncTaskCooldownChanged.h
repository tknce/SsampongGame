// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AsyncTaskCooldownChanged.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCooldownChanged, FGameplayTag, CooldownTag, float, TimeRemaining, float, Duration);
//Gameplay Ability System���� ��ٿ� �±� �迭�� ���� ��ȭ(Begin / End)�� �����ϴ� �����ʸ� �ڵ����� ����ϴ� �������Ʈ ��带 �������,
//AbilitySystemComponent�� GameplayTag�� ���� �̺�Ʈ�� ����ؾ� �մϴ�.
//�Ʒ� ������ ������ UI���� ��ٿ� ��ȭ�� ���� ������ �� �ִ� �����ʸ� ������ �� �ֽ��ϴ�.
// 1. ListenForGameplayTagAddedAndRemoved �Լ� ���
//	AbilitySystemComponent���� �±װ� �߰��ǰų� ���ŵ� �� �̺�Ʈ�� ����� �� �ִ� �Լ����� �ֽ��ϴ�.�̸� ���� �±��� ��ȭ�� ������ �� �ֽ��ϴ�.
//
//	2. Blueprint ��� �ۼ� ����
//	Ability System Component Reference ��������
//	UI���� �÷��̾��� AbilitySystemComponent ������ ����ϴ�.
//
//	�±� �迭�� ��ȸ�ϸ鼭 ������ ���
//	���޹��� �±� �迭�� ��ȸ�ϸ鼭 ������ �±׿� ���� ListenForGameplayTagAddedAndRemoved �Լ��� ȣ���մϴ�.
//
//	�̺�Ʈ ���ε�
//	�±װ� �߰��ǰų� ���ŵǾ��� ���� �̺�Ʈ�� ������ Delegate�� ���ε��Ͽ� UI ������Ʈ�� �����մϴ�.
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class SSAMPONGGAME_API UAsyncTaskCooldownChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCooldownChanged OnCooldownBegin;

	UPROPERTY(BlueprintAssignable)
	FOnCooldownChanged OnCooldownEnd;

	/*��ٿ� GameplayEffects�� ����(Begin)�� ����(End)�� �����ϰ�, ������ ��ٿ� �Ǵ� ���ÿ��� ������ ��ٿ��� Ȯ���ϴ� ������ �߰��� �������Ʈ ��带 �����Ϸ���, ������ ���� ������� �ۼ��� �� �ֽ��ϴ�.

		��� ���� :
		��ٿ��� ���۰� ���� ���� : GameplayTag�� ���� ��ٿ��� ����� GameplayEffect�� ����(Begin)�ǰų� ��(End)���� �� �̺�Ʈ�� ����մϴ�.
		���� ��ٿ� ���� : UseServerCooldown �÷��׸� ���� �������� ����� ��ٿ��� ������� �����մϴ�.�� ���� true�̸� ���� ��ٿ� �ð��� ��ȯ�ϰ�, false�̸� ���ÿ��� ������ ��ٿ��� ��ȯ�մϴ�.
		������ ��ٿ� : ���� ��ٿ��� ����� ���� ���ÿ��� ������ ��ٿ��� �ð��� ���� �ð��� - 1�� ��ȯ�˴ϴ�.*/

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskCooldownChanged* ListenForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTagContainer CooldownTags, bool UseServerCooldown);

	/*UMG �������� �񵿱� �۾�(AsyncTask)�� ��� ���� ��, �������� �񵿱� �۾��� �����ؾ� �ϴ� ��찡 �ֽ��ϴ�.
	Ư�� AsyncTask�� ��ü������ ������� �ʱ� ������, �̸� ������ �������� ������ �޸� ������ ���� ������ �߻��� �� �ֽ��ϴ�.
	UMG ������ �����ֱ⿡�� ������ ���� ������ �����ϴ� ���� �߿��մϴ�.*/
	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayTagContainer CooldownTags;

	bool UseServerCooldown;

	virtual void OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	virtual void CooldownTagChanged(const FGameplayTag CooldownTag, int32 NewCount);

	// ��Ÿ�� ��� ���⼭ �� �����ϸ� �ȴ�.
	bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration);
};
