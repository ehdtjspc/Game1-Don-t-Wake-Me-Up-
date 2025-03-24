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
		FVector ShieldLocation = FoundShield->GetActorLocation();
		FVector ShieldExtent = FoundShield->GetSimpleCollisionCylinderExtent();

		// 몬스터의 현재 위치 가져오기
		AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
		if (!OwnerActor) return EBTNodeResult::Failed;

		FVector MonsterLocation = OwnerActor->GetActorLocation();

		// 몬스터 → 실드 방향 벡터 구하기
		FVector DirectionToShield = (ShieldLocation - MonsterLocation).GetSafeNormal();
		
		// 목표 위치 계산 (실드 반지름 + 50 떨어진 곳)
		FVector TargetLocation = ShieldLocation - (DirectionToShield * (ShieldExtent.X + 0.01));

		// 목표 위치 설정
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPosKey.SelectedKeyName, TargetLocation);

		return EBTNodeResult::Succeeded;


		//float DistanceSq = FVector::DistSquared(MonsterLocation, TargetLocation);
		//if (DistanceSq <= 2500.0f)
		//{

		//}

		//return EBTNodeResult::InProgress;

	}

	//if (NavSystem->GetRandomPointInNavigableRadius(ControllingPawn->GetActorLocation(), SearchRadius, OUT OutPatrolPos))
	//{
	//	OwnerComp.GetBlackboardComponent()->SetValueAsVector(PatrolPosKey.SelectedKeyName, OutPatrolPos);
	//	return EBTNodeResult::Succeeded;
	//}

	return EBTNodeResult::Failed;
}
