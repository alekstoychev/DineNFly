// Fill out your copyright notice in the Description page of Project Settings.


#include "ServingStation.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "FoodResource.h"

#include "RecipesDataTable.h"

AServingStation::AServingStation()
{
	Debug_Score = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Score"));
	Debug_Score->SetupAttachment(RootComponent);

	Debug_Score->SetHorizontalAlignment(EHTA_Center);
	Debug_Score->SetTextRenderColor(FColor::Red);
	Debug_Score->SetWorldSize(80.0f);
	Debug_Score->SetRelativeLocation(FVector(0, 0, 130));
	ScoreString = FString::SanitizeFloat(Score);
	Debug_Score->SetText(FText::FromString(ScoreString));
}

void AServingStation::Interact(AFoodResource*& Resource)
{
	if (IsValid(Resource))
	{
		for (auto& Recipe : Recipes)
		{
			if (Recipe.Key == Resource->GetResourceName())
			{
				Score += Recipe.Value;
				ScoreString = FString::SanitizeFloat(Score);
				Debug_Score->SetText(FText::FromString(ScoreString));

				Resource->Destroy();
				Resource = nullptr;

				UE_LOG(LogTemp, Warning, TEXT("AServingStation::Interact Found Recipe"));

				return;
			}
		}
		//Character has resource, empty station has a resource, but there is no recipe to combine them
		UE_LOG(LogTemp, Error, TEXT("AServingStation::Interact IsValid(Resource)"));
		return;
	}
}

void AServingStation::LoadRecipes(UDataTable* RecipesTable)
{
	if (!IsValid(RecipesTable))
	{
		UE_LOG(LogTemp, Error, TEXT("AServingStation::LoadRecipes !IsValid(Recipes)"));
		return;
	}

	const FString ContextString = "ContextString";

	for (const FName& RecipeRow : RecipesTable->GetRowNames())
	{
		FServingStationRecipesRow* Row = RecipesTable->FindRow<FServingStationRecipesRow>(RecipeRow, ContextString);
		if (Row)
		{
			Recipes.Add(Row->Resource, Row->Result);
			UE_LOG(LogTemp, Warning, TEXT("Loaded Recipe: %s = %.2f"), *Row->Resource, Row->Result);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AServingStation::LoadRecipes Row == nullptr"));
		}
	}
}

void AServingStation::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(BoxCollision))
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AServingStation::OnBeginOverlap);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AServingStation::OnEndOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AServingStation::BeginPlay !IsValid(BoxCollision)"));
	}

	if (IsValid(RecipesToLoad))
	{
		LoadRecipes(RecipesToLoad);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AServingStation::BeginPlay !IsValid(RecipesToLoad)"));
	}
}
