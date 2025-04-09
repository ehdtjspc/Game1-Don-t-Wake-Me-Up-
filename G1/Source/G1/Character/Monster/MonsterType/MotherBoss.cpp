// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/MonsterType/MotherBoss.h"

AMotherBoss::AMotherBoss()
{
	GetMesh()->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));
}

void AMotherBoss::BeginPlay()
{
	Super::BeginPlay();
}

void AMotherBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
