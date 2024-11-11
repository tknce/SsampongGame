// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API USBBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,Category = "AI")
	FBlackboardKeySelector AttackRangedKey;
	// 매틱마다 실행하면 비용이 너무 듬
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
