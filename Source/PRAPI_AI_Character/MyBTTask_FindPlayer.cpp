// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_FindPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_FindPlayer::UMyBTTask_FindPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UMyBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get player character
	if (auto* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		//Get the player's location
		auto const playerLocation = player->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
