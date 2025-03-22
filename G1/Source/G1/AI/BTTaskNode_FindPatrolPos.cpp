// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_FindPatrolPos.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/G1AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/G1GameModeBase.h"
#include "Object/G1Object_Shield.h"


UBTTaskNode_FindPatrolPos::UBTTaskNode_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");

}

EBTNodeResult::Type UBTTaskNode_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation OutPatrolPos;

	if (AActor* FoundShield = UGameplayStatics::GetActorOfClass(GetWorld(), AG1Object_Shield::StaticClass()))
	{
		FVector ShieldLocatuon = FoundShield->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPosKey.SelectedKeyName, ShieldLocatuon);
		return EBTNodeResult::Succeeded;

	}

	//if (NavSystem->GetRandomPointInNavigableRadius(ControllingPawn->GetActorLocation(), SearchRadius, OUT OutPatrolPos))
	//{
	//	OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPosKey.SelectedKeyName, OutPatrolPos);
	//	return EBTNodeResult::Succeeded;
	//}

	return EBTNodeResult::Failed;
}
