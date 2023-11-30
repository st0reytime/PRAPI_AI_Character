// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PRAPI_AI_CHARACTER_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit AMyAIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class UAISenseConfig_Sight* SightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
		void OnTargetDetected(AActor* Acter, FAIStimulus const Stimulus);
};
