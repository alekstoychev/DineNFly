// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractableStation.h"
#include "EmptyStation.generated.h"

/**
 * 
 */
UCLASS()
class DINENFLY_API AEmptyStation : public AIInteractableStation
{
	GENERATED_BODY()
public:
	AEmptyStation();

	virtual void Interact(class AFoodResource*& Resource) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	AFoodResource* HeldResource;
};
