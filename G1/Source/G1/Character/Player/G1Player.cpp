// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/G1Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AG1Player::AG1Player()
{
	SpringArem = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArem"));
	SpringArem->SetupAttachment(GetCapsuleComponent());
	SpringArem->TargetArmLength = 800.0f;
	SpringArem->SetRelativeRotation(FRotator(-40, 0, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArem);
	
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
