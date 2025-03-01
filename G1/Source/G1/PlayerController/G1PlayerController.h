// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "G1PlayerController.generated.h"

struct FInputActionValue;
class UNiagaraSystem;

/**
 *
 */
UCLASS()
class G1_API AG1PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AG1PlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	void TickCursorTrace();

private:
	
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;
	
private:
	FVector CachedDestination;
	float FollowTime;
	bool bMousePressed = false;


protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Character> TargetActor;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Character> HighlightActor;

	
};
