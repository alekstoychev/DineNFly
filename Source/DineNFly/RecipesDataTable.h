// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RecipesDataTable.generated.h"

USTRUCT(BlueprintType)
struct FPlateRecipesRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Resource1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Resource2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Result;
};


USTRUCT(BlueprintType)
struct FChoppingStationRecipesRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Resource;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Result;
};