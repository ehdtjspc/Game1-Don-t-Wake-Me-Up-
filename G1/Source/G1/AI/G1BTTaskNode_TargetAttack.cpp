// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/G1BTTaskNode_TargetAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/G1AIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/G1GameModeBase.h"
#include "Character/Monster/G1Monster.h"

UG1BTTaskNode_TargetAttack::UG1BTTaskNode_TargetAttack()
{
	NodeName = TEXT("TargetAttack1");
}

EBTNodeResult::Type UG1BTTaskNode_TargetAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AG1Monster* Monster = Cast<AG1Monster>(ControllingPawn);
	
	if (Monster != nullptr)
	{
		if (CreatureState == ECreatureState::Dead)
		{
			return EBTNodeResult::Failed; // Dead 상태에서는 실패 반환
		}

		Monster->AttackAction();
		return EBTNodeResult::Succeeded;
	}
	

		return EBTNodeResult::Failed;

}
