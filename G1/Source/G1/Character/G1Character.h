// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/G1HighlightInterface.h"
#include "G1Define.h"
#include "GameplayTagContainer.h"
#include "G1Character.generated.h"

UCLASS()
class G1_API AG1Character : public ACharacter , public IG1HighlightInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AG1Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleGameplayEvent(FGameplayTag EventTag);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Highlight() override;
	virtual void UnHighlight() override;

	virtual void OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker);
	virtual void OnDead(TObjectPtr<AG1Character> Attacker);

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

public:

	UPROPERTY(BlueprintReadWrite)
	ECreatureState CreatureState = ECreatureState::Moving;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Hp = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FinalDamage = 10;
	

};
