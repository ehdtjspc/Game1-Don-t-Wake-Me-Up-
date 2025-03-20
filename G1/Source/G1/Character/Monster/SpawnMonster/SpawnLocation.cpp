// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/SpawnMonster/SpawnLocation.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASpawnLocation::ASpawnLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;

	SpawnBox->SetRelativeScale3D(FVector(20.0f,80.0f,0.0f));

}

// Called when the game starts or when spawned
void ASpawnLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnLocation::GetRandomPoint() const
{
	FVector BoxOrigin = SpawnBox->GetComponentLocation();
	FVector BoxExtent = SpawnBox->GetScaledBoxExtent();


	return UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);
}

FBox ASpawnLocation::GetSpawnBox()
{
	FVector Origin = SpawnBox->GetComponentLocation();
	FVector Extent = SpawnBox->GetScaledBoxExtent();
	return FBox(Origin - Extent, Origin + Extent);
}


