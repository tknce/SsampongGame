// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "AsyncTaskAttributeChanged.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

/**
 * �Ӽ� ��ȭ�� �ɷ� �ο�, �����÷��� ȿ�� ���� ���� ó���մϴ�.
 * UI���� �Ӽ� ��ȭ�� �����ϰ� ���� ��, �Ӽ� ���� �� �̺�Ʈ ����Ͽ� �ش� ��ȭ�� ó���� �� �ֽ��ϴ�.
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class SSAMPONGGAME_API UAsyncTaskAttributeChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;

	// AbilitySystemComponent�� �����Ϸ��� Ư�� FGameplayAttribute�� ���ڷ� �޾Ƽ� �Ӽ� ��ȭ�� ���� delegate�� ���ε��մϴ�.
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskAttributeChanged* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

	// AbilitySystemComponent�� �����Ϸ��� Ư�� FGameplayAttribute�� ���ڷ� �޾Ƽ� �Ӽ� ��ȭ�� ���� delegate�� ���ε��մϴ�.
	// ���� �Ӽ��� �� ���� �����Ϸ���, �Ӽ����� �迭�� �Է¹޾� �� �Ӽ��� ���� ��ȭ�� ������ �� �ִ� ������ ���� �� �ֽ��ϴ�. �� �Ӽ� ���� ��, � �Ӽ��� ����Ǿ����� Ȯ���� �� �ְ� ó���ϴ� ����Դϴ�
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskAttributeChanged* ListenForAttributesChange(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes);

	// AsyncTask�� ����Ͽ� �Ӽ� ��ȭ�� �����ϴ� ���, �񵿱� �۾��� ���� �� �̸� �������� �������־�� �մϴ�.
	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayAttribute AttributeToListenFor;
	TArray<FGameplayAttribute> AttributesToListenFor;

	void AttributeChanged(const FOnAttributeChangeData& Data);
};
