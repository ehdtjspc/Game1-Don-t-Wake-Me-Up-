// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/G1Object.h"
#include "G1Object_Shield.generated.h"

class UShieldAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class G1_API AG1Object_Shield : public AG1Object
{
	GENERATED_BODY()

public:
	AG1Object_Shield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay () override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	virtual UShieldAbilitySystemComponent* GetShieldAbilitySystemComponent();
	virtual void InitAbilityStstem();
protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<class UShieldAbilitySystemComponent> ShieldAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UG1ObjectAttributeSet> ShieldAttributeSet;

};
