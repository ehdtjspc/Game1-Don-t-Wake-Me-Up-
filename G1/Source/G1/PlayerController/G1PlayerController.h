// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "G1PlayerController.generated.h"

struct FInputActionValue;

/**
 *
 */
UCLASS()
class G1_API AG1PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AG1PlayerController(const FObjectInitializer& ObjectInitializer);

private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


protected:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TurnAction;
};
