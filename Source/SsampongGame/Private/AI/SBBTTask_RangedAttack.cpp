// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Mini/SMinionCharacter.h"

USBBTTask_RangedAttack::USBBTTask_RangedAttack()
{
}


EBTNodeResult::Type USBBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ASMinionCharacter* MyPawn = Cast<ASMinionCharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		// 블랙보드에서 설정한 타겟액터 가져오기
		ASBelicaCharacter* TargetActorActor = Cast<ASBelicaCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActorActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		FGameplayTag Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Enemy.Skill.Attack"));
		return MyPawn->TryAttack(Tag, TargetActorActor) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}


