// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "G1Define.h"
#include "BTDecorator_CanAttackShield.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UBTDecorator_CanAttackShield : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CanAttackShield();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetKey2;
	
public:

	UPROPERTY(BlueprintReadWrite)
	ECreatureState CreatureState;

};
