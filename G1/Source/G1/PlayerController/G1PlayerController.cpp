// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/G1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"


AG1PlayerController::AG1PlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void AG1PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

}

void AG1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);

	}
}


void AG1PlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	if (MovementVector.X != 0)
	{
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}

	if (MovementVector.Y != 0)
	{
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}


}

void AG1PlayerController::Input_Turn(const FInputActionValue& InputValue)
{
	float Val = InputValue.Get<float>();
	AddYawInput(Val);
}
