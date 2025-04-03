// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameplayTagContainer.h"
#include "G1AIController.generated.h"

/**
 * 
 */
UCLASS()
class G1_API AG1AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AG1AIController(const FObjectInitializer& ObjectInitializer);
	virtual void OnPossess(APawn* InPawn) override;
	void PlayerAttack();
	virtual void HandleGameplayEvent(FGameplayTag EventTag);
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Monster> G1Monster;

};
