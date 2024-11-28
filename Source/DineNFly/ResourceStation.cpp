// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStation.h"
#include "FoodResource.h"
#include "Components/BoxComponent.h"

AResourceStation::AResourceStation()
{

}

// Called when the game starts or when spawned
void AResourceStation::BeginPlay()
{
	Super::BeginPlay();

	CurrentHeldItem = SpawnResource();
	if (!IsValid(CurrentHeldItem))
	{
		UE_LOG(LogTemp, Error, TEXT("AResourceStation::BeginPlay !IsValid(CurrentHeldItem)"));
		return;
	}

	if (IsValid(BoxCollision))
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AResourceStation::OnBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AResourceStation::OnEndOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AChoppingStation::BeginPlay !IsValid(BoxCollision)"));
	}
}

void AResourceStation::Interact(AFoodResource*& Resource)
{
	if (IsValid(Resource))
	{
		UE_LOG(LogTemp, Error, TEXT("AResourceStation::Interact Already holding a resource"));
		return;
	}

	if (IsValid(CurrentHeldItem))
	{
		Resource = CurrentHeldItem;
		CurrentHeldItem = SpawnResource();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AResourceStation::Interact !IsValid(CurrentHeldItem)"));
		return;
	}
}

// Called every frame
void AResourceStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AFoodResource* AResourceStation::SpawnResource()
{
	if (ResourceToSpawn != " ")
	{
		AFoodResource* SpawnedResource = GetWorld()->SpawnActor<AFoodResource>(ResourceClass);
		if (!IsValid(SpawnedResource))
		{
			UE_LOG(LogTemp, Error, TEXT("AResourceStation::SpawnResource !IsValid(SpawnedResource)"));
			return nullptr;
		}

		FAttachmentTransformRules Trans = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
		SpawnedResource->AttachToActor(this, Trans);
		SpawnedResource->SetActorEnableCollision(false);
		SpawnedResource->SetActorRelativeLocation(FVector(0, 0, 100));
		SpawnedResource->SetResourceName(ResourceToSpawn);

		return SpawnedResource;
	}

	return nullptr;
}
