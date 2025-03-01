// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/G1Monster.h"

AG1Monster::AG1Monster()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

}

void AG1Monster::BeginPlay()
{
	Super::BeginPlay();
}

void AG1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
