// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/G1GameModeBase.h"
#include "Character/Monster/SpawnMonster/SpawnManager.h"
#include "Character/Monster/G1Monster.h"

AG1GameModeBase::AG1GameModeBase()
{

}




void AG1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetASpawnManager();

	if (SpawnManager)
	{
		SpawnMonster();
	}

}


void AG1GameModeBase::GetASpawnManager()
{
	FVector SpawnLocation = FVector(0.f, 0.f, 0.f);  // 예시 위치
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);  // 예시 회전값

	SpawnManager = GetWorld()->SpawnActor<ASpawnManager>(ASpawnManager::StaticClass(), SpawnLocation, SpawnRotation);
}

void AG1GameModeBase::SpawnMonster()
{
	SpawnManager->SpawnMonster();
}


