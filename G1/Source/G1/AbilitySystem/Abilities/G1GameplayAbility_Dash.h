// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "G1GameplayTags.h"
#include "AbilitySystem/Abilities/G1GameplayAbility.h"
#include "G1GameplayAbility_Dash.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1GameplayAbility_Dash : public UG1GameplayAbility
{
	GENERATED_BODY()

public:
	UG1GameplayAbility_Dash(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	


protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags")
	FGameplayTag Tags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UG1AbilitySystemComponent> AbilitySystemComponent;

	//대쉬 관련 코드
	float DashDistance = 1000.f;
	float DashTime = 0.2f;
	bool bCanDash = true;
	float DashColldownTime = 5.0f;





};
