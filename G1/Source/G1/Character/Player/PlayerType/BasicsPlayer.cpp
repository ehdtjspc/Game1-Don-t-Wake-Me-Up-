// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerType/BasicsPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerController/G1PlayerController.h"
#include "AbilitySystem/CharactorAbility/CharactorAbilitySystemComponent.h"
#include "Character/Player/G1PlayerState.h"
#include "AbilitySystem/CharactorAbility/CharactorAttributes/PlayerSet/G1PlayerSet.h"


ABasicsPlayer::ABasicsPlayer()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	WeaponMesh->SetupAttachment(RootComponent);


}

void ABasicsPlayer::BeginPlay()
{
	Super::BeginPlay();

	AG1PlayerState* G1State = Cast<AG1PlayerState>(GetPlayerState());
	if (G1State)
	{
		G1State->SetScore(0.0f);
	}

	if (WeaponMesh && GetMesh())
	{
		WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
			FName("hand_socket_r"));
	}


}

void ABasicsPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void ABasicsPlayer::InitAbilitySystem()
{
	Super::InitAbilitySystem();


}

void ABasicsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicsPlayer::HandleGameplayEvent(FGameplayTag EventTag)
{
	Super::HandleGameplayEvent(EventTag);

}

void ABasicsPlayer::ActivateAbility(FGameplayTag AbilityTag)
{
	Super::ActivateAbility(AbilityTag);

}


