// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/G1HighlightInterface.h"
#include "G1Define.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "G1Character.generated.h"

UCLASS()
class G1_API AG1Character : public ACharacter , public IG1HighlightInterface,public IAbilitySystemInterface
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

	void RefreshHpBarRatio();
	

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void InitAbilitySystem();

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

public:

	UPROPERTY(BlueprintReadWrite)
	ECreatureState CreatureState = ECreatureState::Moving;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> HpBarComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UG1AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UG1AttributeSet> AttributeSet;
	

};
