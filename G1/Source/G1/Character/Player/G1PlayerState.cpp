// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/G1PlayerState.h"
#include "AbilitySystem/G1AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/G1PlayerSet.h"

AG1PlayerState::AG1PlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UG1AbilitySystemComponent>("AbilitySystemComponent");
	PlayerSet = CreateDefaultSubobject<UG1PlayerSet>("PlayerSet");

}

UAbilitySystemComponent* AG1PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAbilitySystemComponent* AG1PlayerState::GetG1AbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UG1PlayerSet* AG1PlayerState::GetG1PlayerSet() const
{
	return PlayerSet;
}
