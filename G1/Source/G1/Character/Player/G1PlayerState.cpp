// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/G1PlayerState.h"
#include "AbilitySystem/CharactorAbility/CharactorAbilitySystemComponent.h"
#include "AbilitySystem/CharactorAbility/CharactorAttributes/PlayerSet/G1PlayerSet.h"
#include "GameMode/G1GameModeBase.h"
#include "Kismet/GameplayStatics.h"

AG1PlayerState::AG1PlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharactorAbilitySystemComponent>("AbilitySystemComponent");
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

void AG1PlayerState::SetScore(const float NewScore)
{
	Super::SetScore(NewScore);

	if (NewScore == 5.0f)
	{
		// 게임모드 가져오기
		AG1GameModeBase* GameMode = Cast<AG1GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->BossSpawn();
		}
	}
}
