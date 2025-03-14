// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Player/G1Player.h"
#include "BasicsPlayer.generated.h"

/**
 * 
 */
UCLASS()
class G1_API ABasicsPlayer : public AG1Player
{
	GENERATED_BODY()
	
public:
	ABasicsPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void InitAbilitySystem() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void HandleGameplayEvent(FGameplayTag EventTag) override;


public:

	virtual void ActivateAbility(FGameplayTag AbilityTag) override;

};
