// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodResource.generated.h"

UCLASS()
class DINENFLY_API AFoodResource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodResource();

	FString GetResourceName() const;

	void SetResourceName(FString& ChangeName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Resource Management")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Resource Management")
	FString ResourceName = "Test";

	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* Debug_FoodNameTag;
};
