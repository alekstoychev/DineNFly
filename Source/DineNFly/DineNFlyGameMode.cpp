// Copyright Epic Games, Inc. All Rights Reserved.

#include "DineNFlyGameMode.h"
#include "DineNFlyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "DineNFlyCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "DineNFlyPlayerController.h"
#include "DineNFlyAIController.h"

ADineNFlyGameMode::ADineNFlyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADineNFlyGameMode::StartPlay()
{
	Super::StartPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("ADineNFlyGameMode::StartPlay !IsValid(PlayerController)"));
		return;
	}

	AActor* PlayerStart1 = FindPlayerStart(PlayerController, "Player1");
	AActor* PlayerStart2 = FindPlayerStart(PlayerController, "Player2");

	if (!IsValid(PlayerStart1))
	{
		UE_LOG(LogTemp, Error, TEXT("ADineNFlyGameMode::StartPlay !IsValid(PlayerStart1)"));
		return;
	}
	if (!IsValid(PlayerStart2))
	{
		UE_LOG(LogTemp, Error, TEXT("ADineNFlyGameMode::StartPlay !IsValid(PlayerStart2)"));
		return;
	}

	ADineNFlyCharacter* SpawnedCharacter1 = Cast<ADineNFlyCharacter>(
		GetWorld()->SpawnActor<AActor>(DefaultPawnClass, PlayerStart1->GetActorLocation(), PlayerStart1->GetActorRotation()));

	if (!IsValid(SpawnedCharacter1))
	{
		UE_LOG(LogTemp, Error, TEXT("ADineNFlyGameMode::StartPlay !IsValid(SpawnedCharacter1)"));
		return;
	}

	ADineNFlyCharacter* SpawnedCharacter2 = Cast<ADineNFlyCharacter>(
		GetWorld()->SpawnActor<AActor>(DefaultPawnClass, PlayerStart2->GetActorLocation(), PlayerStart2->GetActorRotation()));

	if (!IsValid(SpawnedCharacter2))
	{
		UE_LOG(LogTemp, Error, TEXT("ADineNFlyGameMode::StartPlay !IsValid(SpawnedCharacter2)"));
		return;
	}

	ADineNFlyPlayerController* GamePlayerController = Cast<ADineNFlyPlayerController>(PlayerController);
	if (!IsValid(GamePlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("ADineNFlyGameMode::StartPlay !IsValid(GamePlayerController)"));
		return;
	}

	PlayerController->Possess(SpawnedCharacter1);

	ADineNFlyAIController* AIController = GetWorld()->SpawnActor<ADineNFlyAIController>(ADineNFlyAIController::StaticClass());
	if (!IsValid(AIController))
	{
		UE_LOG(LogTemp, Error, TEXT("ADineNFlyGameMode::StartPlay !IsValid(AIController)"));
		return;
	}
	AIController->Possess(SpawnedCharacter2);


	GamePlayerController->SetFirstPlayerCharacter(SpawnedCharacter1);
	GamePlayerController->SetSecondPlayerCharacter(SpawnedCharacter2);
	GamePlayerController->SetupInputComponent();
}