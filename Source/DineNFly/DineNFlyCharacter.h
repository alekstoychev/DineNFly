// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
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
	
protected:

protected:
	// To add mapping context
	virtual void BeginPlay();

private:
	AActor* ItemHold;

	UInputMappingContext* MappingContext;

	UInputAction* MoveAction;

	UInputAction* InteractAction;
};

