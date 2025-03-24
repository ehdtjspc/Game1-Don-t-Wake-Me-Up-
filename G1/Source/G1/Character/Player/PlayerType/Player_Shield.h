// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Player/G1Player.h"
#include "Player_Shield.generated.h"

/**
 * 
 */
UCLASS()
class G1_API APlayer_Shield : public AG1Player
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayer_Shield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

public:
	// Called every frame
	virtual void Tick(float DeltaTime);
	virtual void HandleGameplayEvent(FGameplayTag EventTag) override;
	virtual void ActivateAbility(FGameplayTag AbilityTag) override;
	virtual void InitAbilitySystem() override;


public:


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UNiagaraComponent> NiagaraComponent;





	
};
