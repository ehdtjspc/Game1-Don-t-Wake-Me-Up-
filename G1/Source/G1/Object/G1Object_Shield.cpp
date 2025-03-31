// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/G1Object_Shield.h"
#include "NiagaraComponent.h"
#include "AbilitySystem/ShieldAbility/ShieldAbilitySystemComponent.h"
#include "AbilitySystem/ShieldAbility/ShieldAttributes/G1ObjectAttributeSet.h"

AG1Object_Shield::AG1Object_Shield()
{
	NiagaraComponent =CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));

	RootComponent = NiagaraComponent;

	ShieldAbilitySystemComponent = CreateDefaultSubobject<UShieldAbilitySystemComponent>("ShieldAbilitySystemComponent");
	ShieldAttributeSet = CreateDefaultSubobject<UG1ObjectAttributeSet>("ShieldAttributeSet");
}

void AG1Object_Shield::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityStstem();

}

void AG1Object_Shield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UShieldAbilitySystemComponent* AG1Object_Shield::GetShieldAbilitySystemComponent()
{
	return ShieldAbilitySystemComponent;
}

void AG1Object_Shield::InitAbilityStstem()
{
	ShieldAbilitySystemComponent->InitAbilityActorInfo(this, this);
}
