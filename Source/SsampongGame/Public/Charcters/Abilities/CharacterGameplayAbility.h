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

	// 입력에 반응하여 특정 능력이 자동으로 활성화합니다.
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "Ability")
	DemoAbilityID AbilityInputID = DemoAbilityID::None;

	// 슬롯과 연결 : 입력과 자동으로 연결되지 않는 능력을 슬롯과 연결하기 위한 값입니다.
	//패시브 능력 : 패시브 능력은 입력과 연결되지 않으므로, 능력을 슬롯과 일반적으로 연결할 수 있는 방법이 필요합니다.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	DemoAbilityID AbilityID = DemoAbilityID::None;

	// 이 설정은 능력이 부여되자마자 자동으로 활성화되도록 하여, 패시브 능력이나 타인에게 강제로 적용되는 능력에 유용합니다.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	// 설정을 사용하면 능력을 부여하자마자 자동으로 활성화되며, 프로젝트의 요구에 따라 초기화 작업을 수행할 수 있습니다.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
public:


};
