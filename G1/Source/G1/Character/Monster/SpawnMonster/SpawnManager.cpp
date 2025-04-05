#include "Character/Monster/SpawnMonster/SpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayTagContainer.h"
#include "Character/Monster/G1Monster.h"
#include "Character/Monster/SpawnMonster/SpawnAllLocation.h"
#include "Character/Monster/SpawnMonster/SpawnLocation.h"


// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnManager::SpawnMonster, 5.0f, true);


}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ASpawnManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpawnManager::SpawnMonster()
{
	ASpawnAllLocation* SpawnLocationManager = Cast<ASpawnAllLocation>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnAllLocation::StaticClass()));

	SpawnLocations.Add(SpawnLocationManager->GetSpawnLocation1());
	SpawnLocations.Add(SpawnLocationManager->GetSpawnLocation2());
	SpawnLocations.Add(SpawnLocationManager->GetSpawnLocation3());
	SpawnLocations.Add(SpawnLocationManager->GetSpawnLocation4());

	int32 RandomIndex = FMath::RandRange(0, SpawnLocations.Num() - 1);
	FVector RandomSpawnLocation = SpawnLocations[RandomIndex];
	FRotator SpawnRotation = FRotator::ZeroRotator; // 기본 회전 값

	AG1Monster* SpawnedMonster = GetWorld()->SpawnActor<AG1Monster>(MonsterClass, RandomSpawnLocation, SpawnRotation);
	
}


