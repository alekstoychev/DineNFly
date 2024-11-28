// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyStation.h"
#include "Components/BoxComponent.h"
#include "FoodResource.h"

AEmptyStation::AEmptyStation()
{
}

void AEmptyStation::Interact(AFoodResource*& Resource)
{
	if (IsValid(HeldResource))
	{
		if (IsValid(Resource))
		{
			//Character has resource, empty station has a resource, therefore the character cannot interact with the station
			UE_LOG(LogTemp, Error, TEXT("AEmptyStation::Interact IsValid(Resource)"));
			return;
		}

		Resource = HeldResource;
		HeldResource = nullptr;
	}
	else
	{
		if (!IsValid(Resource))
		{
			UE_LOG(LogTemp, Error, TEXT("AEmptyStation::Interact !IsValid(Resource)"));
			return;
		}

		HeldResource = Resource;

		FAttachmentTransformRules Trans = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
		HeldResource->AttachToActor(this, Trans);
		HeldResource->SetActorRelativeLocation(FVector(0, 0, 100));

		Resource = nullptr;
	}
}

void AEmptyStation::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BoxCollision))
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEmptyStation::OnBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AEmptyStation::OnEndOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AEmptyStation::BeginPlay !IsValid(BoxCollision)"));
	}
}
