// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/G1Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerController/G1PlayerController.h"

AG1Player::AG1Player()
{

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);

	SpringArem = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArem"));
	SpringArem->SetupAttachment(GetCapsuleComponent());
	SpringArem->TargetArmLength = 800.0f;
	SpringArem->SetRelativeRotation(FRotator(-60, 0, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArem);
	Camera->bUsePawnControlRotation = false;
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
}

void AG1Player::BeginPlay()
{
	Super::BeginPlay();
}

void AG1Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AG1Player::HandleGameplayEvent(FGameplayTag EventTag)
{
	AG1PlayerController* PC = Cast<AG1PlayerController>(GetController());

	if (PC)
	{
		PC->HandleGameplayEvent(EventTag);
	}
}
