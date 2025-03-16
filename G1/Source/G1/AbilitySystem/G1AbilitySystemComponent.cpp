// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/G1AbilitySystemComponent.h"
#include "G1GameplayTags.h"

void UG1AbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities)
{
	for (auto& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);
		
		auto& a = ActivatableAbilities;

		//TryActivateAbility(SpecHandle);
		//GiveAbilityAndActivateOnce(AbilitySpec);
		SpecHandles.Add(SpecHandle);
	}

	
}

void UG1AbilitySystemComponent::ActivateAbility(FGameplayTag AbilityTag)
{
	FGameplayAbilitySpecHandle& Attack = SpecHandles[0];
	FGameplayAbilitySpecHandle& Dash = SpecHandles[1];
	FGameplayAbilitySpecHandle& DontBotherMe = SpecHandles[2];

	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		if (AbilityTag == G1GameplayTags::Ability_Attack)
		{
			TryActivateAbility(Attack);
		}
		// TODO
		
		if (AbilityTag == G1GameplayTags::Ability_Dash)
		{
			TryActivateAbility(Dash);
		}

		if (AbilityTag == G1GameplayTags::Ability_DontBotherMe)
		{
			TryActivateAbility(DontBotherMe);
		}
		
	}
}



