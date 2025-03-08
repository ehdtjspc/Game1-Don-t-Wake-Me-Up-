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

		auto Action1 = InputData->FindInputActionByTag(G1GameplayTags::Input_Action_SetDestination);

		// Setup mouse input events
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Completed, this, &ThisClass::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Canceled, this, &ThisClass::OnSetDestinationReleased);



	}
}

void AG1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	TickCursorTrace();

	ChaseTargetAndAttack();

	if (GetCharacter()->GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr) == false)
	{
		SetCreatureState(ECreatureState::Moving);
	}

}

void AG1PlayerController::HandleGameplayEvent(FGameplayTag EventTag)
{
	if (EventTag.MatchesTag(G1GameplayTags::Event_Montage_Attack))
	{
		if (TargetActor)
		{
			TargetActor->OnDamaged(10, G1Player);
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
	if (TargetActor == nullptr)
	{
		return;
	}

	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

	FVector Direction = TargetActor->GetActorLocation() - G1Player->GetActorLocation();
	if (Direction.Length() < 400.f)     //거리 안에 들어오면 공격 
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, TEXT("Attack"));

		if (AttackMontage)
		{
			
			if (bMousePressed)
			{
				//if (GetCharacter()->GetMesh()->GetAnimInstance()->Montage_IsPlaying(nullptr) == false)
				//TargetActor->OnDamaged(G1Player->FinalDamage,G1Player);


				FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(G1Player->GetActorLocation(), TargetActor->GetActorLocation());
				G1Player->SetActorRotation(Rotator);

				GetCharacter()->PlayAnimMontage(AttackMontage);
				SetCreatureState(ECreatureState::Skill);

				TargetActor = HighlightActor;
			}
			else
			{
				TargetActor = nullptr;
			}
		}


	}
	else          //아니면 따라가기
	{
		FVector WorldDirection = Direction.GetSafeNormal();   // Normal값을 가져온다.
		G1Player->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AG1PlayerController::OnInputStarted()
{
	StopMovement();
	bMousePressed = true;
	TargetActor = HighlightActor;
}

// Triggered every frame when the input is held down
void AG1PlayerController::OnSetDestinationTriggered()
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


void AG1PlayerController::OnSetDestinationReleased()
{
	bMousePressed = false;

	if (GetCreatureState() == ECreatureState::Skill)
	{
		return;
	}

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

