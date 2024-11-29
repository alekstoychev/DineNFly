// Fill out your copyright notice in the Description page of Project Settings.


#include "EmptyStation.h"
#include "Components/BoxComponent.h"
#include "FoodResource.h"

#include "RecipesDataTable.h"

AEmptyStation::AEmptyStation()
{
}

void AEmptyStation::Interact(AFoodResource*& Resource)
{
	if (IsValid(HeldResource))
	{
		if (IsValid(Resource))
		{
			TPair<FString, FString> RecipeIngredients = TPair<FString, FString>(HeldResource->GetResourceName(), Resource->GetResourceName());
			TPair<FString, FString> RecipeIngredientsPermuted = TPair<FString, FString>(Resource->GetResourceName(), HeldResource->GetResourceName());
			for (auto& Recipe : Recipes)
			{
				if (Recipe.Key == RecipeIngredients || Recipe.Key == RecipeIngredientsPermuted)
				{
					FString* Result = Recipes.Find(RecipeIngredients);
					if (Result == nullptr)
					{
						Result = Recipes.Find(RecipeIngredientsPermuted);
					}

					FAttachmentTransformRules Trans = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
					HeldResource->AttachToActor(this, Trans);
					HeldResource->SetActorRelativeLocation(FVector(0, 0, 100));

					HeldResource->SetResourceName(*Result);
					Resource->Destroy();
					Resource = nullptr;

					UE_LOG(LogTemp, Warning, TEXT("AEmptyStation::Interact Found Recipe"));

					return;
				}
			}
			//Character has resource, empty station has a resource, but there is no recipe to combine them
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

void AEmptyStation::LoadRecipes(UDataTable* RecipesTable)
{
	if (!IsValid(RecipesTable))
	{
		UE_LOG(LogTemp, Error, TEXT("AEmptyStation::LoadRecipes !IsValid(Recipes)"));
		return;
	}

	const FString ContextString = "ContextString";

	for (const FName& RecipeRow : RecipesTable->GetRowNames())
	{
		FPlateRecipesRow* Row = RecipesTable->FindRow<FPlateRecipesRow>(RecipeRow, ContextString);
		if (Row)
		{
			TPair<FString, FString> Resources = TPair<FString, FString>(Row->Resource1, Row->Resource2);
			Recipes.Add(Resources, Row->Result);
			UE_LOG(LogTemp, Warning, TEXT("Loaded Recipe: %s + %s = %s"), *Row->Resource1, *Row->Resource2, *Row->Result);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AEmptyStation::LoadRecipes Row == nullptr"));
		}
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

	if (IsValid(RecipesToLoad))
	{
		LoadRecipes(RecipesToLoad);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AEmptyStation::BeginPlay !IsValid(RecipesToLoad)"));
	}
}
