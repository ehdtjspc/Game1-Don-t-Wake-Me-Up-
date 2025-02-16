// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/G1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/G1AssetManager.h"
#include "Data/G1InputData.h"
#include "G1GameplayTags.h"

AG1PlayerController::AG1PlayerController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
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

}

void AG1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const UG1InputData* InputData = UG1AssetManager::GetAssetByName<UG1InputData>("InputData"))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

		auto Action1 = InputData->FindInputActionByTag(G1GameplayTags::Input_Action_Move);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);

		auto Action2 = InputData->FindInputActionByTag(G1GameplayTags::Input_Action_Turn);
		EnhancedInputComponent->BindAction(Action2, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);
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
