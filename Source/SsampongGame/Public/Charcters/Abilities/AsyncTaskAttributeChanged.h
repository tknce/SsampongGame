// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "AsyncTaskAttributeChanged.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

/**
 * 속성 변화나 능력 부여, 게임플레이 효과 관리 등을 처리합니다.
 * UI에서 속성 변화를 감지하고 싶을 때, 속성 변경 시 이벤트 등록하여 해당 변화를 처리할 수 있습니다.
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class SSAMPONGGAME_API UAsyncTaskAttributeChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;

	// AbilitySystemComponent와 추적하려는 특정 FGameplayAttribute를 인자로 받아서 속성 변화에 대한 delegate를 바인딩합니다.
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskAttributeChanged* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

	// AbilitySystemComponent와 추적하려는 특정 FGameplayAttribute를 인자로 받아서 속성 변화에 대한 delegate를 바인딩합니다.
	// 여러 속성을 한 번에 추적하려면, 속성들의 배열을 입력받아 각 속성에 대한 변화를 감지할 수 있는 버전을 만들 수 있습니다. 각 속성 변경 시, 어떤 속성이 변경되었는지 확인할 수 있게 처리하는 방식입니다
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskAttributeChanged* ListenForAttributesChange(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes);

	// AsyncTask를 사용하여 속성 변화를 추적하는 경우, 비동기 작업이 끝날 때 이를 수동으로 종료해주어야 합니다.
	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayAttribute AttributeToListenFor;
	TArray<FGameplayAttribute> AttributesToListenFor;

	void AttributeChanged(const FOnAttributeChangeData& Data);
};
