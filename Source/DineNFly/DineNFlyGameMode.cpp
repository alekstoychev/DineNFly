// Copyright Epic Games, Inc. All Rights Reserved.

#include "DineNFlyGameMode.h"
#include "DineNFlyCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADineNFlyGameMode::ADineNFlyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
