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
		FVector StartLocation = G1Monster->GetActorLocation();   //�����߻�
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

				if (HitActor) // HitActor ��ȿ�� Ȯ��
				{
					AG1Player* Player = Cast<AG1Player>(HitActor); // AG1Monster Ÿ������ ĳ����
					if (Player) // ĳ���� ���� Ȯ��
					{
						// �÷��̾�� Ÿ�� ��� ������ �Ÿ� ���
						float Distance = FVector::Dist(G1Monster->GetActorLocation(), HitActor->GetActorLocation());

						// �Ÿ��� 150 ������ ��쿡�� OnDamaged ȣ��
						if (Distance <= 160.0f)
						{
							// OnDamaged �Լ� ȣ��
							Player->OnDamaged(10, G1Monster);
						}
					}
				}
			}
		}
	}

}