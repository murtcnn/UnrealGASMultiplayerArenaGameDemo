// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASMultiplayerArenaGameMode.h"
#include "GASMultiplayerArenaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGASMultiplayerArenaGameMode::AGASMultiplayerArenaGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
