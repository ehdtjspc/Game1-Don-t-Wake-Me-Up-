// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/PlayerType/BasicsPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerController/G1PlayerController.h"
#include "AbilitySystem/G1AbilitySystemComponent.h"
#include "Character/Player/G1PlayerState.h"
#include "AbilitySystem/Attributes/G1PlayerSet.h"


ABasicsPlayer::ABasicsPlayer()
{

}

void ABasicsPlayer::BeginPlay()
{
	Super::BeginPlay();


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


