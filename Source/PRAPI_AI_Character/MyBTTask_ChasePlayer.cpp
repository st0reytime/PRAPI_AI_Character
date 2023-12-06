// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ChasePlayer.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UMyBTTask_ChasePlayer::UMyBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UMyBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get target location from blockboard via npc controller
	if (auto* const cont = Cast<AMyAIController>(OwnerComp.GetAIOwner()))
	{
		auto const playerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		//Move to player location
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, playerLocation);

		//Finish with success
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
