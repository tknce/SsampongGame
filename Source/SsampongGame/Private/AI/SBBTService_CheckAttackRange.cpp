// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void USBBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 엑터와의 거리를 확인

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (ensure(Blackboard))
	{
		AActor* Targetactor = Cast<AActor>(Blackboard->GetValueAsObject("TargetActor"));
		if(Targetactor)
		{
			AAIController* mycontroller = OwnerComp.GetAIOwner();
			if(ensure(mycontroller))
			{
				APawn* AIPawn = mycontroller->GetPawn();
				if(ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(Targetactor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithinRange = DistanceTo < 2000.f;
					bool bHasLOS = false;

					if(bWithinRange)
						bHasLOS = mycontroller->LineOfSightTo(Targetactor);

					Blackboard->SetValueAsBool(AttackRangedKey.SelectedKeyName, bWithinRange && bHasLOS);
				}
			}
		}
	}
}
