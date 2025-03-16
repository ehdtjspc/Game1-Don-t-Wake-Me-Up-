// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/G1GameplayAbility_Dash.h"
#include "Character/Player/G1Player.h"
#include "G1GameplayTags.h"
#include "AbilitySystem/G1AbilitySystemComponent.h"
#include "Character/Player/G1PlayerState.h"


UG1GameplayAbility_Dash::UG1GameplayAbility_Dash(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}



bool UG1GameplayAbility_Dash::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}

	return true;
}

void UG1GameplayAbility_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	// Do Something
	if (AttackMontage)
	{
		
			AG1Player* Player = Cast<AG1Player>(ActorInfo->AvatarActor);
			Player->PlayAnimMontage(AttackMontage);

			FVector PlayerForward = Player->GetActorForwardVector();
			FVector PlayerLocation = Player->GetActorLocation();
			FVector DashTargetLocation = PlayerLocation + PlayerForward * DashDistance;
			Player->LaunchCharacter(PlayerForward * DashDistance / DashTime, true, true);

		
	}
}

void UG1GameplayAbility_Dash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

