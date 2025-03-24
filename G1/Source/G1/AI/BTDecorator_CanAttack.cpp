// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CanAttack.h"
#include "G1AIController.h"
#include "Character/G1Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Player/G1Player.h"
#include "Object/G1Object_Shield.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	AG1Player* Target1 = Cast<AG1Player>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey1.SelectedKeyName));
	
	if (Target1 == nullptr)
	{
		return false;
	}

	return (Target1->GetDistanceTo(ControllingPawn) <= 200);


	

}
