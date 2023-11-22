// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindPatrolPoint.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAI.h"

UMyBTTask_FindPatrolPoint::UMyBTTask_FindPatrolPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Patrol Point");
}

EBTNodeResult::Type UMyBTTask_FindPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the enemy AI controller
	if (auto* const cont = Cast<AMyAIController>(OwnerComp.GetAIOwner()))
	{
		//Get blackboard component from behvior tree
		if (auto* const bc = OwnerComp.GetBlackboardComponent())
		{
			//Get current patrol path index from blackboard
			auto const index = bc->GetValueAsInt(GetSelectedBlackboardKey());
			//Get the enemy
			if (auto* enemy = Cast<AEnemyAI>(cont->GetPawn()))
			{
				//Get the current patrol path vector from ai - this is local to patrol path actor
				auto const point = enemy->GetPatrolPath()->GetPatrolPoint(index);

				//convert local vector to a global point
				auto const globalPoint = enemy->GetPatrolPath()->GetActorTransform().TransformPosition(point);
				bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, globalPoint);

				//Finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
