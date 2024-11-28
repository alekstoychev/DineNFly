// Fill out your copyright notice in the Description page of Project Settings.


#include "DineNFlyPlayerController.h"
#include "DineNFlyCharacter.h"
#include "InputTriggers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ADineNFlyPlayerController::SetFirstPlayerCharacter(ADineNFlyCharacter* CharacterToAdd)
{
    Character1 = CharacterToAdd;
}

void ADineNFlyPlayerController::SetSecondPlayerCharacter(ADineNFlyCharacter* CharacterToAdd)
{
    Character2 = CharacterToAdd;
}

void ADineNFlyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!bAreSettingsBound)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

        if (Subsystem)
        {
            if (KeyboardMappingContext)
            {
                Subsystem->AddMappingContext(KeyboardMappingContext, 0);
            }
            if (ControllerMappingContext)
            {
                Subsystem->AddMappingContext(ControllerMappingContext, 0);
            }
        }

        // Bind handlers for movement and other actions
        if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
        {
            EnhancedInputComponent->BindAction(KeyboardMoveAction, ETriggerEvent::Triggered, this, &ADineNFlyPlayerController::KeyboardMove);
            EnhancedInputComponent->BindAction(KeyboardInteractAction, ETriggerEvent::Started, this, &ADineNFlyPlayerController::KeyboardInteract);

            EnhancedInputComponent->BindAction(ControllerMoveAction, ETriggerEvent::Triggered, this, &ADineNFlyPlayerController::ControllerMove);
            EnhancedInputComponent->BindAction(ControllerInteractAction, ETriggerEvent::Started, this, &ADineNFlyPlayerController::ControllerInteract);

            bAreSettingsBound = true;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ADineNFlyPlayerController::SetupInputComponent Settings already bound"));
    }
}

void ADineNFlyPlayerController::KeyboardMove(const FInputActionValue& Value)
{
    if (!IsValid(Character1))
    {
        UE_LOG(LogTemp, Error, TEXT("ADineNFlyPlayerController::KeyboardMove !IsValid(Character1)"));
        return;
    }
    Character1->StopInteract();
    Character1->Move(Value);
}

void ADineNFlyPlayerController::KeyboardInteract()
{
    if (!IsValid(Character1))
    {
        UE_LOG(LogTemp, Error, TEXT("ADineNFlyPlayerController::KeyboardInteract !IsValid(Character1)"));
        return;
    }
    Character1->Interact();
}

void ADineNFlyPlayerController::ControllerMove(const FInputActionValue& Value)
{
    if (!IsValid(Character2))
    {
        UE_LOG(LogTemp, Error, TEXT("ADineNFlyPlayerController::ControllerMove !IsValid(Character2)"));
        return;
    }
    Character2->StopInteract();
    Character2->Move(Value);
}

void ADineNFlyPlayerController::ControllerInteract()
{
    if (!IsValid(Character2))
    {
        UE_LOG(LogTemp, Error, TEXT("ADineNFlyPlayerController::ControllerInteract !IsValid(Character2)"));
        return;
    }
    Character2->Interact();
}