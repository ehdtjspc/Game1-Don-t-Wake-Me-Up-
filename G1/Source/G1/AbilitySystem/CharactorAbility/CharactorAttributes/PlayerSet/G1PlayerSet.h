// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/CharactorAbility/CharactorAttributes/G1AttributeSet.h"
#include "G1PlayerSet.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1PlayerSet : public UG1AttributeSet
{
	GENERATED_BODY()
	
public:
	UG1PlayerSet();

};


// 플레이어만 가지고 있는 골드나 경험치 등 여기다가 넣기