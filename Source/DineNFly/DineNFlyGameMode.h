// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DineNFlyGameMode.generated.h"

UCLASS(minimalapi)
class ADineNFlyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADineNFlyGameMode();

	void StartPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> PlayerCharacter1;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> PlayerCharacter2;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AChoppingStation> ChoppingStation;

};



