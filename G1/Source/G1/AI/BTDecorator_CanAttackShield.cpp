// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CanAttackShield.h"
#include "G1AIController.h"
#include "Character/G1Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Player/G1Player.h"
#include "Object/G1Object_Shield.h"


UBTDecorator_CanAttackShield::UBTDecorator_CanAttackShield()
{
	NodeName = TEXT("CanShieldAttack");
}

bool UBTDecorator_CanAttackShield::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	AG1Object_Shield* Target2 = Cast<AG1Object_Shield>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey2.SelectedKeyName));
	if (Target2 == nullptr)
	{
		return false;
	}
	bool bIsInRange;
	return(bIsInRange = FVector::Dist(Target2->GetActorLocation(), ControllingPawn->GetActorLocation()) < 800 && CreatureState != ECreatureState::Dead );


}
