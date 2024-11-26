// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodResource.h"

#include "Components/TextRenderComponent.h"

// Sets default values
AFoodResource::AFoodResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;

	Debug_FoodNameTag = CreateDefaultSubobject<UTextRenderComponent>(TEXT("FoodName"));
	Debug_FoodNameTag->SetupAttachment(RootComponent);

	Debug_FoodNameTag->SetHorizontalAlignment(EHTA_Center);
	Debug_FoodNameTag->SetTextRenderColor(FColor::Green);
	Debug_FoodNameTag->SetWorldSize(50.0f);
	Debug_FoodNameTag->SetRelativeLocation(FVector(0, 0, 100));
}

FString AFoodResource::GetResourceName() const
{
	return ResourceName;
}

void AFoodResource::SetResourceName(FString& ChangeName)
{
	if (!ChangeName.IsEmpty() || ChangeName != "")
	{
		ResourceName = ChangeName;

		Debug_FoodNameTag->SetText(FText::FromString(ResourceName));
	}
}

// Called when the game starts or when spawned
void AFoodResource::BeginPlay()
{
	Super::BeginPlay();

	Debug_FoodNameTag->SetText(FText::FromString(ResourceName));
	
}

// Called every frame
void AFoodResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

