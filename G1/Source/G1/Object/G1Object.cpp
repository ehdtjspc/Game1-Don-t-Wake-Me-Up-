// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/G1Object.h"

// Sets default values
AG1Object::AG1Object()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AG1Object::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AG1Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AG1Object::OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker)
{
}

void AG1Object::OnDead(TObjectPtr<AG1Character> Attacker)
{
}

