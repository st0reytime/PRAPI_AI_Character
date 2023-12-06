// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "EnemyAI.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "PRAPI_AI_CharacterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem();
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

void AMyAIController::SetupPerceptionSystem()
{
	//Create sight perception system
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		//create and set perception component
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 500.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);//Time after player is forgotten once seen
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 500.f;//Determines how close stimulus source has to be from original location to keep being seen
		//Create different categories for stimulus
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void AMyAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto* const ch = Cast<APRAPI_AI_CharacterCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}
