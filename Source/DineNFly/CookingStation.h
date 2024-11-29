// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractableStation.h"
#include "CookingStation.generated.h"

/**
 * 
 */
UCLASS()
class DINENFLY_API ACookingStation : public AIInteractableStation
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACookingStation();

	virtual void Interact(class AFoodResource*& Resource) override;

	virtual void LoadRecipes(class UDataTable* Recipes) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PauseCooking();

private:
	// First item is the required resource
	// Second item is the resulting resource
	UPROPERTY(EditAnywhere, Category = "Recipes")
	TMap<FString, FString> Recipes;

	UPROPERTY(EditAnywhere, Category = "Recipes", meta = (Units = "Seconds"))
	float CookingTime = 4.f;

	float RemainingCookingTime = 0.f;

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* CountdownText;

	bool isCookingComplete;
	void FTimerHandlerCompleteCooking();

	UPROPERTY(VisibleAnywhere)
	AFoodResource* HeldResource;

	FTimerHandle TimerHandleCooking;

	void UpdateCountdownText();
};
