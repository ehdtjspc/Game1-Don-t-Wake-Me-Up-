// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "G1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class G1_API AG1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AG1GameModeBase();
	void OnGameOver();
	void BossSpawn();


protected:
	virtual void BeginPlay() override;
private:

	UPROPERTY()
	TObjectPtr<class ASpawnManager> SpawnManger;


};
