// Fill out your copyright notice in the Description page of Project Settings.


#include "IInteractableStation.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

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
	BoxCollision->SetRelativeLocation(FVector(0, 100, 0));
	BoxCollision->SetMobility(EComponentMobility::Static);
}

void AIInteractableStation::Interact(AFoodResource*& Resource)
{
	UE_LOG(LogTemp, Warning, TEXT("AIInteractableStation::Interact"));
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

