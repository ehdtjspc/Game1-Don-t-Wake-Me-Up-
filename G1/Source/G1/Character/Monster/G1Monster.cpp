// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Monster/G1Monster.h"
#include "AbilitySystem/CharactorAbility/CharactorAbilitySystemComponent.h"
#include "AbilitySystem/CharactorAbility/CharactorAttributes/MonsterSet/G1MonsterSet.h"
#include "AI/G1AIController.h"


AG1Monster::AG1Monster()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	AbilitySystemComponent = CreateDefaultSubobject<UCharactorAbilitySystemComponent>("AbilitySystemComponent");

	AttributeSet = CreateDefaultSubobject<UG1MonsterSet>("MonsterSet");

}

void AG1Monster::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystem();

}

void AG1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AG1Monster::InitAbilitySystem()
{
	Super::InitAbilitySystem();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AG1Monster::OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker)
{
	Super::OnDamaged(Damage,Attacker);
}

void AG1Monster::AttackAction()
{
	/*AG1AIController* Pc = Cast<AG1AIController>(GetController());
	if (Pc)
	{
		Pc->PlayerAttack();
	}
	*/
	PlayerAttack();
}

void AG1Monster::PlayerAttack()
{
	PlayAnimMontage(AttackMontage);

}

void AG1Monster::HandleGameplayEvent(FGameplayTag EventTag)
{
	AG1AIController* PC = Cast<AG1AIController>(GetController());

	if (CreatureState != ECreatureState::Dead)
	{
		if (PC)
		{
			PC->HandleGameplayEvent(EventTag);
		}
	}
}



