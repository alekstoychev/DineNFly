// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoppingStation.h"

#include "FoodResource.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "DineNFlyCharacter.h"

AChoppingStation::AChoppingStation()
{
	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownText"));
	CountdownText->SetupAttachment(RootComponent);

	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetTextRenderColor(FColor::Red);
	CountdownText->SetWorldSize(50.0f);
	CountdownText->SetRelativeLocation(FVector(0, 0, 100));

	FString CountdownString = FString::Printf(TEXT(" "));
	CountdownText->SetText(FText::FromString(CountdownString));
}

void AChoppingStation::Interact(AFoodResource*& Resource)
{
	if (!IsValid(HeldResource))
	{
		if (!IsValid(Resource))
		{
			UE_LOG(LogTemp, Error, TEXT("AChoppingStation::Interact !IsValid(Resource)"));
			return;
		}

		for (auto& Recipe : Recipes)
		{
			if (Recipe.Key == Resource->GetResourceName())
			{
				HeldResource = Resource; 

				FAttachmentTransformRules Trans = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
				HeldResource->AttachToActor(this, Trans);
				HeldResource->SetActorRelativeLocation(FVector(0, 0, 100));

				Resource = nullptr;

				UE_LOG(LogTemp, Warning, TEXT("AChoppingStation::Interact Found Recipe"));

				if (!GetWorldTimerManager().IsTimerActive(TimerHandleChopping))
				{
					GetWorldTimerManager().SetTimer(TimerHandleChopping, this, 
						&AChoppingStation::FTimerHandlerCompleteChopping, ChoppingTime, false);
					UE_LOG(LogTemp, Warning, TEXT("AChoppingStation::Interact called TimerHandleChopping"));
					RemainingChoppingTime = ChoppingTime;
				}

				return;
			}
		}
	}
	else if (isChoppingComplete)
	{
		Resource = HeldResource;
		HeldResource = nullptr;
		isChoppingComplete = false;

		UE_LOG(LogTemp, Warning, TEXT("AChoppingStation::Interact Meal Taken"));
	}
}

void AChoppingStation::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BoxCollision))
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AChoppingStation::OnBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AChoppingStation::OnEndOverlap);
	}
}

void AChoppingStation::Tick(float DeltaTime)
{
	if (RemainingChoppingTime > 0.f)
	{
		RemainingChoppingTime -= DeltaTime;
		UpdateCountdownText();
	}
}

void AChoppingStation::FTimerHandlerCompleteChopping()
{
	isChoppingComplete = true;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FString* Result = Recipes.Find(HeldResource->GetResourceName());
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AChoppingStation::FTimerHandlerCompleteChopping (Result == nullptr)"));
		return;
	}

	HeldResource->SetResourceName(*Result);

	FString CountdownString = FString::Printf(TEXT(" "));
	CountdownText->SetText(FText::FromString(CountdownString));

	UE_LOG(LogTemp, Warning, TEXT("AChoppingStation::FTimerHandlerCompleteChopping Chopping Complete"));
}

void AChoppingStation::UpdateCountdownText()
{
	if (RemainingChoppingTime > 0.f)
	{
		FString CountdownString = FString::Printf(TEXT("%.1f"), RemainingChoppingTime);
		CountdownText->SetText(FText::FromString(CountdownString));
	}
}

void AChoppingStation::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADineNFlyCharacter* PlayerCharacter = Cast<ADineNFlyCharacter>(OtherActor);
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetNearbyStation(this);
	}
}

void AChoppingStation::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADineNFlyCharacter* PlayerCharacter = Cast<ADineNFlyCharacter>(OtherActor);
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetNearbyStation(nullptr);
	}
}
