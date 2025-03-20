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
	
	void GetASpawnManager();

	void SpawnMonster();


protected:
	virtual void BeginPlay() override;
	
private:

   UPROPERTY(EditAnywhere, Category = "Spawn")
   TObjectPtr<class ASpawnManager> SpawnManager;
};
