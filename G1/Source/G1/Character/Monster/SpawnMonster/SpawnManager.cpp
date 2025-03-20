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
	


}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, TEXT("avasfdasd"));


}

// Called to bind functionality to input
void ASpawnManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpawnManager::SpawnMonster()
{
	ASpawnAllLocation* SpawnLocationManager = Cast<ASpawnAllLocation>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnAllLocation::StaticClass()));

	FVector SpawnLocation = SpawnLocationManager->GetSpawnLocation1();
	FRotator SpawnRotation = FRotator::ZeroRotator; // 기본 회전 값

	AActor* SpawnedMonster = GetWorld()->SpawnActor<AActor>(MonsterClass, SpawnLocation, SpawnRotation);

}


