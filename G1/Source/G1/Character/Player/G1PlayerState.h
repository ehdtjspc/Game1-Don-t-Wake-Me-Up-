// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "G1PlayerState.generated.h"

class UG1PlayerSet;

class UCharactorAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class G1_API AG1PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AG1PlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAbilitySystemComponent* GetG1AbilitySystemComponent() const;
	UG1PlayerSet* GetG1PlayerSet() const;

	virtual void SetScore(const float NewScore);

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TObjectPtr<UCharactorAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UG1PlayerSet> PlayerSet;

	
};
