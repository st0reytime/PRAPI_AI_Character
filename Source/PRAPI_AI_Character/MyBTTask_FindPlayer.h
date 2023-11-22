// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FindPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PRAPI_AI_CHARACTER_API UMyBTTask_FindPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UMyBTTask_FindPlayer(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
