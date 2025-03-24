// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindShield.h"
#include "AI/G1AIController.h"
#include "Character/G1Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"
#include "Character/Player/G1Player.h"
#include "Object/G1Object_Shield.h"

UBTService_FindShield::UBTService_FindShield()
{
	NodeName = TEXT("FindShieldTargetService");
	Interval = 0.5f;
}

void UBTService_FindShield::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(SearchRadius),
		CollisionQueryParam
	);

	if (bResult)
	{

		for (FOverlapResult& OverlapResult : OverlapResults)
		{
		
			AG1Object_Shield* G1Shield = Cast<AG1Object_Shield>(OverlapResult.GetActor());
			if (G1Shield)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey2.SelectedKeyName, G1Shield);
				DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Green, false, 0.2f);
				return;
			}

		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey2.SelectedKeyName, nullptr);

	DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Red, false, 0.2f);
}
