// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/G1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/G1AssetManager.h"
#include "Data/G1InputData.h"
#include "G1GameplayTags.h"
#include "Character/Player/G1Player.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Monster/G1Monster.h"



AG1PlayerController::AG1PlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AG1PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (const UG1InputData* InputData = UG1AssetManager::GetAssetByName<UG1InputData>("InputData"))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}

	G1Player =Cast<AG1Player>(GetCharacter());

}

void AG1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const UG1InputData* InputData = UG1AssetManager::GetAssetByName<UG1InputData>("InputData"))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		auto ActionMove = InputData->FindInputActionByTag(G1GameplayTags::Input_Action_SetDestination);
		auto ActionAttack = InputData->FindInputActionByTag(G1GameplayTags::Input_Action_BasicAttack);

		// Setup mouse input events
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Started, this, &ThisClass::OnMoveStarted);
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &ThisClass::OnMoveTriggered);
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Completed, this, &ThisClass::OnMoveReleased);
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Canceled, this, &ThisClass::OnMoveReleased);

		EnhancedInputComponent->BindAction(ActionAttack, ETriggerEvent::Started, this, &ThisClass::OnAttackStarted);
		EnhancedInputComponent->BindAction(ActionAttack, ETriggerEvent::Triggered, this, &ThisClass::OnAttackTriggered);
		EnhancedInputComponent->BindAction(ActionAttack, ETriggerEvent::Completed, this, &ThisClass::OnAttackReleased);
		EnhancedInputComponent->BindAction(ActionAttack, ETriggerEvent::Canceled, this, &ThisClass::OnAttackReleased);


	}
}

void AG1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	TickCursorTrace();


	if (GetCharacter()->GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr) == false)
	{
		SetCreatureState(ECreatureState::Moving);
	}

}

void AG1PlayerController::HandleGameplayEvent(FGameplayTag EventTag)
{
	if (EventTag.MatchesTag(G1GameplayTags::Event_Montage_Attack))
	{
		// 라인 트레이스 시작 위치 및 방향 설정
		FVector StartLocation = G1Player->GetActorLocation();
		FVector ForwardVector = G1Player->GetActorForwardVector();
		FVector EndLocation = StartLocation + ForwardVector * 150.0f; // 캐릭터 전방 150 위치
		// 라인 트레이스 수행
		TArray<FHitResult> HitResults; // 여러 개의 트레이스 결과를 저장할 배열

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(G1Player); // G1Player를 무시 목록에 추가

		if (UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartLocation, EndLocation, 50.0f, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true))
		{
			for (FHitResult HitResult : HitResults)
			{
				AActor* HitActor = HitResult.GetActor();

				if (HitActor) // HitActor 유효성 확인
				{
					AG1Monster* Monster = Cast<AG1Monster>(HitActor); // AG1Monster 타입으로 캐스팅
					if (Monster) // 캐스팅 성공 확인
					{
						// HitActor가 몬스터 타입인지 확인 (예시: AMonster 클래스)
						if (HitActor->IsA(AG1Monster::StaticClass()))
						{
							// 플레이어와 타격 대상 사이의 거리 계산
							float Distance = FVector::Dist(G1Player->GetActorLocation(), HitActor->GetActorLocation());

							// 거리가 150 이하일 경우에만 OnDamaged 호출
							if (Distance <= 160.0f)
							{
								// OnDamaged 함수 호출
								Monster->OnDamaged(10, G1Player);
							}
						}
					}
				}
			}
		}
	}
}

void AG1PlayerController::TickCursorTrace()
{
	if (bMousePressed)
	{
		return;
	}

	FHitResult OutCursorHit;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT OutCursorHit) == false)
	{
		return;
	}

	AG1Character* LocalHighlightActor = Cast<AG1Character>(OutCursorHit.GetActor());
	if (LocalHighlightActor == nullptr)
	{
		// 있었는데 없어지는 상황
		if (HighlightActor)
		{
			HighlightActor->UnHighlight();
		}
	}
	else
	{
		if (HighlightActor)
		{
			// 원래 있었는데 ,다른 애로 교체함
			if (HighlightActor != LocalHighlightActor)
			{
				HighlightActor->UnHighlight();
				LocalHighlightActor->Highlight();
			}

			//동일한 애라면 무시한다.
		}
		else
		{
			//원래 없었고 새로운 타겟
			LocalHighlightActor->Highlight();
		}
	}

	HighlightActor = LocalHighlightActor;
}

void AG1PlayerController::ChaseTargetAndAttack()
{
	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}
	StopMovement();

	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, TEXT("Attack"));

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);
	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	FVector StartLocation = G1Player->GetActorLocation();
	FRotator Rotation = (CachedDestination - StartLocation).Rotation();

	// 캐릭터가 이 방향을 바라보도록 회전시킴
	G1Player->SetActorRotation(Rotation);  // 캐릭터의 회전값을 설정



	// 공격 애니메이션 실행


	// -----------------------------------------------------
	// 실험

	// 범위 안에 들어오면 피달게하기 허공때려도
	G1Player->ActivateAbility(G1GameplayTags::Ability_Attack);
	SetCreatureState(ECreatureState::Skill);
	TargetActor = HighlightActor;

}



void AG1PlayerController::OnMoveStarted()
{
	StopMovement();
	SetCreatureState(ECreatureState::Moving); // 이동 상태로 설정
	TargetActor = HighlightActor;
}

// Triggered every frame when the input is held down
void AG1PlayerController::OnMoveTriggered()
{
	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	if (TargetActor)
	{
		return;
	}

	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (G1Player)
	{
		FVector WorldDirection = (CachedDestination - G1Player->GetActorLocation()).GetSafeNormal();
		G1Player->AddMovementInput(WorldDirection, 1.0, false);
	}


}


void AG1PlayerController::OnMoveReleased()
{

	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}
	
	SetCreatureState(ECreatureState::None);

	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		if (TargetActor == nullptr)
		{
			// We move there and spawn some particles
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}

	}
	FollowTime = 0.f;


}

void AG1PlayerController::OnAttackStarted()       //공격 부분
{
	bMousePressed = true;
	TargetActor = HighlightActor;

}

void AG1PlayerController::OnAttackTriggered()        //공격 부분
{
	ChaseTargetAndAttack();
}

void AG1PlayerController::OnAttackReleased()        //공격 부분
{
	bMousePressed = false;

	

}

ECreatureState AG1PlayerController::GetCreatureState()
{
	if (G1Player)
	{
		return G1Player->CreatureState;
	}

	return ECreatureState::None;
}

void AG1PlayerController::SetCreatureState(ECreatureState InState)
{
	if (G1Player)
	{
		G1Player->CreatureState = InState;
	}
}

