// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractableStation.h"
#include "ServingStation.generated.h"

/**
 * 
 */
UCLASS()
class DINENFLY_API AServingStation : public AIInteractableStation
{
	GENERATED_BODY()
	

public:
	AServingStation();

private:
	virtual void Interact(class AFoodResource*& Resource) override;

	virtual void LoadRecipes(class UDataTable* RecipesTable) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TMap<FString, float> Recipes;

	float Score = 0;

	FString ScoreString;

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* Debug_Score;
};
