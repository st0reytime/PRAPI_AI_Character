// Copyright Epic Games, Inc. All Rights Reserved.

#include "PRAPI_AI_CharacterGameMode.h"
#include "PRAPI_AI_CharacterCharacter.h"
#include "UObject/ConstructorHelpers.h"

APRAPI_AI_CharacterGameMode::APRAPI_AI_CharacterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
