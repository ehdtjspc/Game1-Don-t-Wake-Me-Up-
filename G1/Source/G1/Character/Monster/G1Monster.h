// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/G1Character.h"
#include "G1Define.h"
#include "GameplayTagContainer.h"
#include "G1Monster.generated.h"

/**
 * 
 */
UCLASS()
class G1_API AG1Monster : public AG1Character
{
	GENERATED_BODY()
public:
	AG1Monster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void InitAbilitySystem() override;

	virtual void OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker) override;

	virtual void PossessedBy(AController* NewController) override;

	void AttackAction();

	void PlayerAttack();

	virtual void HandleGameplayEvent(FGameplayTag EventTag);



public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackMontage;

};
