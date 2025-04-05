// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/G1GameModeBase.h"
#include "Character/Monster/SpawnMonster/SpawnManager.h"
#include "Character/Monster/G1Monster.h"
#include "Kismet/GameplayStatics.h"

AG1GameModeBase::AG1GameModeBase()
{

}


void AG1GameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void AG1GameModeBase::OnGameOver()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}







