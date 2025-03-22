// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/G1Object_Shield.h"
#include "NiagaraComponent.h"

AG1Object_Shield::AG1Object_Shield()
{
	NiagaraComponent =CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));

	RootComponent = NiagaraComponent;

}

void AG1Object_Shield::BeginPlay()
{
	Super::BeginPlay();
}

void AG1Object_Shield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
