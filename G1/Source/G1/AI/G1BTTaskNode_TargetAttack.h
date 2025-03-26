// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "G1Define.h"
#include "G1BTTaskNode_TargetAttack.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1BTTaskNode_TargetAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UG1BTTaskNode_TargetAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(BlueprintReadWrite)
	ECreatureState CreatureState;


};
