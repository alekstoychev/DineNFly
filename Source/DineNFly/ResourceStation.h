// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractableStation.h"
#include "ResourceStation.generated.h"

/**
 * 
 */
UCLASS()
class DINENFLY_API AResourceStation : public AIInteractableStation
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AResourceStation();

	virtual void Interact(class AFoodResource*& Resource) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	FString ResourceToSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFoodResource> ResourceClass;

	class AFoodResource* CurrentHeldItem;

	AFoodResource* SpawnResource();
};
