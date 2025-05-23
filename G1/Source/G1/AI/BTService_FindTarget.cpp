// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindTarget.h"
#include "AI/G1AIController.h"
#include "Character/G1Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"
#include "Character/Player/G1Player.h"
#include "Object/G1Object_Shield.h"

UBTService_FindTarget::UBTService_FindTarget()
{
	NodeName = TEXT("FindTargetService");
	Interval = 0.5f;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* LocalPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (LocalPawn == nullptr)
	{
		return;
	}

	UWorld* World = LocalPawn->GetWorld();
	if (World == nullptr)
	{
		return;
	}

	FVector Location = LocalPawn->GetActorLocation();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, LocalPawn);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		CollisionQueryParam
	);

	if (bResult)
	{


		for (FOverlapResult& OverlapResult : OverlapResults)
		{
			AG1Player* G1Player = Cast<AG1Player>(OverlapResult.GetActor());
			if (G1Player)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey1.SelectedKeyName, G1Player);
				DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Green, false, 0.2f);
				return;
			}

		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey1.SelectedKeyName, nullptr);

	DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Red, false, 0.2f);
}

