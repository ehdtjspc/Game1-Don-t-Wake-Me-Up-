// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "G1GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UG1GameInstance(const FObjectInitializer& ObjectInitializer);

public:
	virtual void Init() override;  //시작할때 실행
	virtual void Shutdown() override; // 끝날때 실행
};
