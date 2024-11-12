// Fill out your copyright notice in the Description page of Project Settings.


#include "DineNFlyPlayerCharacter.h"

// Sets default values
ADineNFlyPlayerCharacter::ADineNFlyPlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADineNFlyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADineNFlyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADineNFlyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

