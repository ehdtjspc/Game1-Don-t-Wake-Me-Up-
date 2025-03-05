// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "G1Define.h"


// Sets default values
AG1Character::AG1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AG1Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AG1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AG1Character::HandleGameplayEvent(FGameplayTag EventTag)
{

}

// Called to bind functionality to input
void AG1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AG1Character::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AG1Character::UnHighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void AG1Character::OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker)
{
	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	if (Hp == 0)
	{
		OnDead(Attacker);
	}

	D(FString::Printf(TEXT("%d"), Hp));

}

void AG1Character::OnDead(TObjectPtr<AG1Character> Attacker)
{
	if (CreatureState == ECreatureState::Dead)
	{
		CreatureState = ECreatureState::Dead;
	}
}

