// Copyright Epic Games, Inc. All Rights Reserved.

#include "FastestGameMode.h"
#include "FastestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFastestGameMode::AFastestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
