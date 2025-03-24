// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindShield.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UBTService_FindShield : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_FindShield();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SearchRadius = 500.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector TargetKey2;

};
