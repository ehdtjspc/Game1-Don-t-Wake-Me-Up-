// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/G1AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Character/Monster/G1Monster.h"
#include "G1GameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Player/G1Player.h"



AG1AIController::AG1AIController(const FObjectInitializer& ObjectInitializer)
{
}

void AG1AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AG1AIController::HandleGameplayEvent(FGameplayTag EventTag)
{
	if (EventTag.MatchesTag(G1GameplayTags::Event_Montage_Attack))
	{
		PlayerAttack();
	}
}

void AG1AIController::SetControlledMonster(AG1Monster* Monster)
{
	G1Monster = Monster;
}

void AG1AIController::BeginPlay()
{
	Super::BeginPlay();

	G1Monster=Cast<AG1Monster>(GetCharacter());
}

void AG1AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AG1AIController::PlayerAttack()
{
	if (G1Monster)
	{
		FVector StartLocation = G1Monster->GetActorLocation();   //오류발생
		FVector ForwardVector = G1Monster->GetActorForwardVector();
		FVector EndLocation = StartLocation + ForwardVector * 150.0f;

		TArray<FHitResult> HitResults;

		ActorsToIgnore;
		ActorsToIgnore.Add(G1Monster);

		if (UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartLocation, EndLocation, 50.0f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true))
		{
			for (const FHitResult HitResult : HitResults)
			{
				AActor* HitActor = HitResult.GetActor();

				if (HitActor) // HitActor 유효성 확인
				{
					AG1Player* Player = Cast<AG1Player>(HitActor); // AG1Monster 타입으로 캐스팅
					if (Player) // 캐스팅 성공 확인
					{
						// 플레이어와 타격 대상 사이의 거리 계산
						float Distance = FVector::Dist(G1Monster->GetActorLocation(), HitActor->GetActorLocation());

						// 거리가 150 이하일 경우에만 OnDamaged 호출
						if (Distance <= 160.0f)
						{
							// OnDamaged 함수 호출
							Player->OnDamaged(10, G1Monster);
						}
					}
				}
			}
		}
	}

}