// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "EnemyAI.h"

AMyAIController::AMyAIController(FObjectInitializer const& ObjectInitializer)
{
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AEnemyAI* const enemy = Cast<AEnemyAI>(InPawn))//Check we are possessing enemy
	{
		if (UBehaviorTree* const tree = enemy->GetBehaviorTree())//Check if behavior tree is there
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
