// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "G1Define.h"
#include "GameplayTagContainer.h"
#include "Character/G1Character.h"
#include "G1Object.generated.h"

UCLASS()
class G1_API AG1Object : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AG1Object();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime);

public:
	virtual void OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker);
	virtual void OnDead(TObjectPtr<AG1Character> Attacker);

public:

	UPROPERTY(BlueprintReadWrite)
	ECreatureState CreatureState = ECreatureState::None;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UNiagaraComponent> NiagaraComponent;


};
