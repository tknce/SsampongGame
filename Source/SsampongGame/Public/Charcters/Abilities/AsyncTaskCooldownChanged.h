// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AsyncTaskCooldownChanged.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCooldownChanged, FGameplayTag, CooldownTag, float, TimeRemaining, float, Duration);
//Gameplay Ability System에서 쿨다운 태그 배열에 대해 변화(Begin / End)를 감지하는 리스너를 자동으로 등록하는 블루프린트 노드를 만들려면,
//AbilitySystemComponent의 GameplayTag에 대한 이벤트를 사용해야 합니다.
//아래 절차를 따르면 UI에서 쿨다운 변화를 쉽게 감지할 수 있는 리스너를 설정할 수 있습니다.
// 1. ListenForGameplayTagAddedAndRemoved 함수 사용
//	AbilitySystemComponent에는 태그가 추가되거나 제거될 때 이벤트를 등록할 수 있는 함수들이 있습니다.이를 통해 태그의 변화를 감지할 수 있습니다.
//
//	2. Blueprint 노드 작성 예시
//	Ability System Component Reference 가져오기
//	UI에서 플레이어의 AbilitySystemComponent 참조를 얻습니다.
//
//	태그 배열을 순회하면서 리스너 등록
//	전달받은 태그 배열을 순회하면서 각각의 태그에 대해 ListenForGameplayTagAddedAndRemoved 함수를 호출합니다.
//
//	이벤트 바인딩
//	태그가 추가되거나 제거되었을 때의 이벤트를 각각의 Delegate에 바인딩하여 UI 업데이트를 수행합니다.
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class SSAMPONGGAME_API UAsyncTaskCooldownChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCooldownChanged OnCooldownBegin;

	UPROPERTY(BlueprintAssignable)
	FOnCooldownChanged OnCooldownEnd;

	/*쿨다운 GameplayEffects의 시작(Begin)과 종료(End)를 감지하고, 서버의 쿨다운 또는 로컬에서 예측된 쿨다운을 확인하는 로직을 추가한 블루프린트 노드를 구현하려면, 다음과 같은 방식으로 작성할 수 있습니다.

		기능 설명 :
		쿨다운의 시작과 끝을 감지 : GameplayTag를 통해 쿨다운이 적용된 GameplayEffect가 시작(Begin)되거나 끝(End)났을 때 이벤트를 등록합니다.
		서버 쿨다운 감지 : UseServerCooldown 플래그를 통해 서버에서 적용된 쿨다운을 사용할지 결정합니다.이 값이 true이면 서버 쿨다운 시간을 반환하고, false이면 로컬에서 예측된 쿨다운을 반환합니다.
		예측된 쿨다운 : 서버 쿨다운을 사용할 때는 로컬에서 예측된 쿨다운의 시간과 지속 시간이 - 1로 반환됩니다.*/

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskCooldownChanged* ListenForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTagContainer CooldownTags, bool UseServerCooldown);

	/*UMG 위젯에서 비동기 작업(AsyncTask)을 사용 중일 때, 수동으로 비동기 작업을 종료해야 하는 경우가 있습니다.
	특히 AsyncTask는 자체적으로 종료되지 않기 때문에, 이를 적절히 관리하지 않으면 메모리 누수와 같은 문제가 발생할 수 있습니다.
	UMG 위젯의 생명주기에서 적절한 종료 시점을 설정하는 것이 중요합니다.*/
	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayTagContainer CooldownTags;

	bool UseServerCooldown;

	virtual void OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	virtual void CooldownTagChanged(const FGameplayTag CooldownTag, int32 NewCount);

	// 쿨타임 계산 여기서 쿨감 설정하면 된다.
	bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration);
};
