// Copyright Epic Games, Inc. All Rights Reserved.

#include "NinjaNekoGameMode.h"
#include "NinjaNekoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANinjaNekoGameMode::ANinjaNekoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
