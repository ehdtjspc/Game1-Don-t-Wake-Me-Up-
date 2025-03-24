// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerType/Player_Shield.h"
#include "NiagaraComponent.h"


APlayer_Shield::APlayer_Shield()
{
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));

	RootComponent = NiagaraComponent;
}

void APlayer_Shield::BeginPlay()
{
	Super::BeginPlay();

}

void APlayer_Shield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayer_Shield::HandleGameplayEvent(FGameplayTag EventTag)
{
	Super::HandleGameplayEvent(EventTag);

}

void APlayer_Shield::ActivateAbility(FGameplayTag AbilityTag)
{
	Super::ActivateAbility(AbilityTag);

}

void APlayer_Shield::InitAbilitySystem()
{
	Super::InitAbilitySystem();

}

