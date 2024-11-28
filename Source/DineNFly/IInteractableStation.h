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

	virtual void LoadRecipes(class UDataTable* Recipes);
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
	FVector BoxCollisionSize = FVector(75.f, 75.f, 112.5f);

	UPROPERTY(EditAnywhere, Category = "Recipes")
	class UDataTable* RecipesToLoad;

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* Debug_StationName;


	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
