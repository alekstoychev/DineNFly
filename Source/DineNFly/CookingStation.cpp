// Fill out your copyright notice in the Description page of Project Settings.


#include "CookingStation.h"

#include "FoodResource.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"

#include "RecipesDataTable.h"

ACookingStation::ACookingStation()
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

void ACookingStation::Interact(AFoodResource*& Resource)
{
	if (IsValid(HeldResource))
	{
		if (IsValid(Resource))
		{
			//Character has resource, cooking station has a resource, therefore the character cannot interact with the station
			UE_LOG(LogTemp, Error, TEXT("ACookingStation::Interact IsValid(Resource)"));
			return;
		}

		if (isCookingComplete)
		{
			Resource = HeldResource;
			HeldResource = nullptr;
			isCookingComplete = false;

			UE_LOG(LogTemp, Warning, TEXT("ACookingStation::Interact Meal Taken"));
		}
		else if (GetWorldTimerManager().IsTimerPaused(TimerHandleCooking))
		{
			GetWorldTimerManager().UnPauseTimer(TimerHandleCooking);
			UE_LOG(LogTemp, Warning, TEXT("ACookingStation::Interact unpaused TimerHandleChopping"));
		}
	}
	else
	{
		if (!IsValid(Resource))
		{
			UE_LOG(LogTemp, Error, TEXT("ACookingStation::Interact !IsValid(Resource)"));
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

				UE_LOG(LogTemp, Warning, TEXT("ACookingStation::Interact Found Recipe"));

				if (!GetWorldTimerManager().IsTimerActive(TimerHandleCooking))
				{
					GetWorldTimerManager().SetTimer(TimerHandleCooking, this,
						&ACookingStation::FTimerHandlerCompleteCooking, CookingTime, false);
					UE_LOG(LogTemp, Warning, TEXT("ACookingStation::Interact set TimerHandleCooking"));
					RemainingCookingTime = CookingTime;
				}

				return;
			}
		}
	}
}

void ACookingStation::LoadRecipes(UDataTable* RecipesTable)
{
	if (!IsValid(RecipesTable))
	{
		UE_LOG(LogTemp, Error, TEXT("ACookingStation::LoadRecipes !IsValid(Recipes)"));
		return;
	}

	const FString ContextString = "ContextString";

	for (const FName& RecipeRow : RecipesTable->GetRowNames())
	{
		FChoppingStationRecipesRow* Row = RecipesTable->FindRow<FChoppingStationRecipesRow>(RecipeRow, ContextString);
		if (Row)
		{
			Recipes.Add(Row->Resource, Row->Result);
			UE_LOG(LogTemp, Warning, TEXT("Loaded Recipe: %s = %s"), *Row->Resource, *Row->Result);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ACookingStation::LoadRecipes Row == nullptr"));
		}
	}
}

void ACookingStation::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BoxCollision))
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACookingStation::OnBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACookingStation::OnEndOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ACookingStation::BeginPlay !IsValid(BoxCollision)"));
	}

	if (IsValid(RecipesToLoad))
	{
		LoadRecipes(RecipesToLoad);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ACookingStation::BeginPlay !IsValid(RecipesToLoad)"));
	}
}

void ACookingStation::Tick(float DeltaTime)
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandleCooking) && RemainingCookingTime > 0.f)
	{
		RemainingCookingTime -= DeltaTime;
		UpdateCountdownText();
	}
}

void ACookingStation::PauseCooking()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandleCooking))
	{
		GetWorldTimerManager().PauseTimer(TimerHandleCooking);
		UE_LOG(LogTemp, Warning, TEXT("ACookingStation::PauseCooking paused TimerHandleCooking"));
	}
}

void ACookingStation::FTimerHandlerCompleteCooking()
{
	isCookingComplete = true;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FString* Result = Recipes.Find(HeldResource->GetResourceName());
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACookingStation::FTimerHandlerCompleteCooking (Result == nullptr)"));
		return;
	}

	HeldResource->SetResourceName(*Result);

	FString CountdownString = FString::Printf(TEXT(" "));
	CountdownText->SetText(FText::FromString(CountdownString));

	UE_LOG(LogTemp, Warning, TEXT("ACookingStation::FTimerHandlerCompleteCooking Cooking Complete"));
}

void ACookingStation::UpdateCountdownText()
{
	if (RemainingCookingTime > 0.f)
	{
		FString CountdownString = FString::Printf(TEXT("%.1f"), RemainingCookingTime);
		CountdownText->SetText(FText::FromString(CountdownString));
	}
}
