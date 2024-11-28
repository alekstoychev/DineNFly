// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractableStation.h"
#include "ChoppingStation.generated.h"

/**
 * 
 */
UCLASS()
class DINENFLY_API AChoppingStation : public AIInteractableStation
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChoppingStation();

	virtual void Interact(class AFoodResource*& Resource) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PauseChopping();

private:
	// First item is the required resource
	// Second item is the resulting resource
	UPROPERTY(EditAnywhere, Category = "Recipes")
	TMap<FString, FString> Recipes;

	UPROPERTY(EditAnywhere, Category = "Recipes", meta = (Units = "Seconds"))
	float ChoppingTime = 4.f;

	float RemainingChoppingTime = 0.f;

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* CountdownText;

	bool isChoppingComplete;
	void FTimerHandlerCompleteChopping();

	UPROPERTY(VisibleAnywhere)
	AFoodResource* HeldResource;

	FTimerHandle TimerHandleChopping;

	void UpdateCountdownText();


	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
