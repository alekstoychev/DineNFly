// Fill out your copyright notice in the Description page of Project Settings.


#include "IInteractableStation.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "DineNFlyCharacter.h"

#include "RecipesDataTable.h"

// Sets default values
AIInteractableStation::AIInteractableStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetMobility(EComponentMobility::Static);
	SetRootComponent(StaticMeshComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);

	BoxCollision->SetBoxExtent(BoxCollisionSize);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxCollision->SetRelativeLocation(FVector(110, 0, 120));
	BoxCollision->SetMobility(EComponentMobility::Static);

	Debug_StationName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DebugStationName"));
	Debug_StationName->SetupAttachment(RootComponent);

	Debug_StationName->SetHorizontalAlignment(EHTA_Center);
	Debug_StationName->SetTextRenderColor(FColor::Red);
	Debug_StationName->SetWorldSize(50.0f);
	Debug_StationName->SetRelativeLocation(FVector(0, 0, 200));

	Debug_StationName->SetText(FText::FromString(GetActorNameOrLabel()));
}

void AIInteractableStation::Interact(AFoodResource*& Resource)
{
	UE_LOG(LogTemp, Warning, TEXT("AIInteractableStation::Interact"));
}

void AIInteractableStation::LoadRecipes(UDataTable* Recipes)
{
	UE_LOG(LogTemp, Warning, TEXT("AIInteractableStation::LoadRecipes"));
}

// Called when the game starts or when spawned
void AIInteractableStation::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIInteractableStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AIInteractableStation::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADineNFlyCharacter* PlayerCharacter = Cast<ADineNFlyCharacter>(OtherActor);
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetNearbyStation(this);
	}
}

void AIInteractableStation::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ADineNFlyCharacter* PlayerCharacter = Cast<ADineNFlyCharacter>(OtherActor);
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetNearbyStation(nullptr);
	}
}
