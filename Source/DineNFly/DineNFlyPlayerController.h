// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DineNFlyPlayerController.generated.h"

class ADineNFlyCharacter;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class DINENFLY_API ADineNFlyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetFirstPlayerCharacter(ADineNFlyCharacter* CharacterToAdd);
	void SetSecondPlayerCharacter(ADineNFlyCharacter* CharacterToAdd);
	
	virtual void SetupInputComponent() override;
private:

	ADineNFlyCharacter* Character1 = nullptr;
	ADineNFlyCharacter* Character2 = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* KeyboardMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* ControllerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* KeyboardMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ControllerMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* KeyboardInteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ControllerInteractAction;

	void KeyboardMove(const FInputActionValue& Value);
	void KeyboardInteract();

	void ControllerMove(const FInputActionValue& Value);	
	void ControllerInteract();

	bool bAreSettingsBound = false;
};
