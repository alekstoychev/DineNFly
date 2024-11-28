// Copyright Epic Games, Inc. All Rights Reserved.

#include "DineNFlyCharacter.h"
#include "ChoppingStation.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "IInteractableStation.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADineNFlyCharacter

ADineNFlyCharacter::ADineNFlyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ADineNFlyCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	ItemHold = GetWorld()->SpawnActor<AFoodResource>(Debug_FoodTest);
	if (!IsValid(ItemHold))
	{
		UE_LOG(LogTemp, Warning, TEXT("ADineNFlyCharacter::BeginPlay !IsValid(ItemHold)"));
	}

	FAttachmentTransformRules Trans = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	ItemHold->AttachToActor(this, Trans);
	ItemHold->SetActorEnableCollision(false);
	ItemHold->SetActorRelativeLocation(FVector(100, 0, 0));
}

void ADineNFlyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (!IsValid(Controller))
	{
		UE_LOG(LogTemp, Warning, TEXT("ADineNFlyCharacter::Move !IsValid(Controller)"));
		return;
	}

	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FVector::ForwardVector;
	
	// get right vector 
	const FVector RightDirection = FVector::RightVector;

	// add movement 
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ADineNFlyCharacter::SetNearbyStation(AIInteractableStation* station)
{
	NearbyInteractableStation = station;
}

void ADineNFlyCharacter::StopInteract()
{
	AChoppingStation* NearbyChoppingStation = Cast<AChoppingStation>(NearbyInteractableStation);
	if (IsValid(NearbyChoppingStation))
	{
		NearbyChoppingStation->PauseChopping();
	}
}

void ADineNFlyCharacter::Interact()
{
	if (IsValid(NearbyInteractableStation))
	{
		NearbyInteractableStation->Interact(ItemHold);
		if (IsValid(ItemHold))
		{
			FAttachmentTransformRules Trans = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
			ItemHold->AttachToActor(this, Trans);
			ItemHold->SetActorRelativeLocation(FVector(100, 0, 0));
		}
	}
}