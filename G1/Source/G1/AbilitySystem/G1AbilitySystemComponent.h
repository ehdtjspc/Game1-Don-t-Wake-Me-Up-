// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "G1AbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	
	void AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities);

	void ActivateAbility(FGameplayTag AbilityTag);


	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> SpecHandles;

	UPROPERTY()
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitySpecMap;

	UPROPERTY()
	UG1AbilitySystemComponent* AbilitySysytemComponent;



};
