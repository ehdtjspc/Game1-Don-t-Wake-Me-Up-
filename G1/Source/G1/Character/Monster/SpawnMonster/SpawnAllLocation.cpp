// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/SpawnMonster/SpawnAllLocation.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Monster/SpawnMonster/SpawnLocation.h"
#include "GameplayTagContainer.h"
#include "Character/Monster/G1Monster.h"


// Sets default values
ASpawnAllLocation::ASpawnAllLocation()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnAllLocation::BeginPlay()
{
	Super::BeginPlay();
	FindSpawnAreas();
	
}

// Called every frame
void ASpawnAllLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpawnAllLocation::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ASpawnAllLocation::GetSpawnLocation1()
{
	// 랜덤으로 위치를 추출할 SpawnLocation을 고른다.
	if (SpawnLocations.Num() > 0)
	{
		// 랜덤한 SpawnLocation을 고른다.
	
		ASpawnLocation* SelectedSpawnLocation1 = SpawnLocations[0];


		// 박스 범위 가져오기
		FBox SpawnBox1 = SelectedSpawnLocation1->GetSpawnBox();


		// 랜덤한 X, Y, Z 좌표 생성 (박스 안에서)
		float SpawnBox1X = FMath::RandRange(SpawnBox1.Min.X, SpawnBox1.Max.X);
		float SpawnBox1Y = FMath::RandRange(SpawnBox1.Min.Y, SpawnBox1.Max.Y);
		float SpawnBox1Z = FMath::RandRange(SpawnBox1.Min.Z, SpawnBox1.Max.Z);

		// 랜덤한 위치 반환
		return FVector(SpawnBox1X, SpawnBox1Y, SpawnBox1Z);
	}

	// SpawnLocation이 없을 경우 기본값 반환
	return FVector::ZeroVector;
}

FVector ASpawnAllLocation::GetSpawnLocation2()
{
	if (SpawnLocations.Num() > 0)
	{

		ASpawnLocation* SelectedSpawnLocation2 = SpawnLocations[1];

		FBox SpawnBox2 = SelectedSpawnLocation2->GetSpawnBox();

		// 랜덤한 X, Y, Z 좌표 생성 (박스 안에서)
		float SpawnBox2X = FMath::RandRange(SpawnBox2.Min.X, SpawnBox2.Max.X);
		float SpawnBox2Y = FMath::RandRange(SpawnBox2.Min.Y, SpawnBox2.Max.Y);
		float SpawnBox2Z = FMath::RandRange(SpawnBox2.Min.Z, SpawnBox2.Max.Z);

		return FVector(SpawnBox2X, SpawnBox2Y, SpawnBox2Z);
	}

	// SpawnLocation이 없을 경우 기본값 반환
	return FVector::ZeroVector;
}

FVector ASpawnAllLocation::GetSpawnLocation3()
{

	if (SpawnLocations.Num() > 0)
	{
		ASpawnLocation* SelectedSpawnLocation3 = SpawnLocations[2];

		FBox SpawnBox3 = SelectedSpawnLocation3->GetSpawnBox();

		// 랜덤한 X, Y, Z 좌표 생성 (박스 안에서)
		float SpawnBox3X = FMath::RandRange(SpawnBox3.Min.X, SpawnBox3.Max.X);
		float SpawnBox3Y = FMath::RandRange(SpawnBox3.Min.Y, SpawnBox3.Max.Y);
		float SpawnBox3Z = FMath::RandRange(SpawnBox3.Min.Z, SpawnBox3.Max.Z);

		return FVector(SpawnBox3X, SpawnBox3Y, SpawnBox3Z);
	}

	// SpawnLocation이 없을 경우 기본값 반환
	return FVector::ZeroVector;
}

FVector ASpawnAllLocation::GetSpawnLocation4()
{
	if (SpawnLocations.Num() > 0)
	{
		ASpawnLocation* SelectedSpawnLocation4 = SpawnLocations[3];

		FBox SpawnBox4 = SelectedSpawnLocation4->GetSpawnBox();

		// 랜덤한 X, Y, Z 좌표 생성 (박스 안에서)
		float SpawnBox4X = FMath::RandRange(SpawnBox4.Min.X, SpawnBox4.Max.X);
		float SpawnBox4Y = FMath::RandRange(SpawnBox4.Min.Y, SpawnBox4.Max.Y);
		float SpawnBox4Z = FMath::RandRange(SpawnBox4.Min.Z, SpawnBox4.Max.Z);

		return FVector(SpawnBox4X, SpawnBox4Y, SpawnBox4Z);
	}

	// SpawnLocation이 없을 경우 기본값 반환
	return FVector::ZeroVector;
}



void ASpawnAllLocation::FindSpawnAreas()
{

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("SpawnLocation_All"), FoundActors); // "SpawnPoint" 태그가 있는 액터만 가져오기

	SpawnLocations.Empty(); // 기존 데이터 초기화

	for (AActor* Actor : FoundActors)
	{
		ASpawnLocation* SpawnLocation = Cast<ASpawnLocation>(Actor);
		if (SpawnLocation)
		{
			SpawnLocations.Add(SpawnLocation);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT(" %d"), SpawnLocations.Num());

}
