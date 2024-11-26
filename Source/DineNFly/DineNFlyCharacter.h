// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "FoodResource.h"
#include "DineNFlyCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ADineNFlyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADineNFlyCharacter();

	void Interact();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	void SetNearbyStation(class AIInteractableStation* station);
protected:
	// To add mapping context
	virtual void BeginPlay();

private:
	UPROPERTY(VisibleAnywhere, Category = "amongus")
	AFoodResource* ItemHold;

	UPROPERTY(EditAnywhere, Category = "amongus")
	TSubclassOf<AFoodResource> Debug_FoodTest;

	UPROPERTY(VisibleAnywhere, Category = "amongus")
	AIInteractableStation* NearbyInteractableStation;

	UPROPERTY()
	UInputMappingContext* MappingContext;

	UPROPERTY()
	UInputAction* MoveAction;

	UPROPERTY()
	UInputAction* InteractAction;
};

