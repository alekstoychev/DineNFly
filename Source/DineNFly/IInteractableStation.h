// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"
#include "IInteractableStation.generated.h"

UCLASS()
class DINENFLY_API AIInteractableStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIInteractableStation();

	virtual void Interact(class AFoodResource*& Resource);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Interaction Zone")
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Interaction Zone")
	FVector BoxCollisionSize = FVector(100.f, 100.f, 100.f);
};
