// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Monster/G1Monster.h"
#include "MotherMonster.generated.h"

/**
 * 
 */
UCLASS()
class G1_API AMotherMonster : public AG1Monster
{
	GENERATED_BODY()

public:
	AMotherMonster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
