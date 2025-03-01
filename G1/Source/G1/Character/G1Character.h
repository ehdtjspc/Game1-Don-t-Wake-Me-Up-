// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/G1HighlightInterface.h"
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Highlight() override;
	virtual void UnHighlight() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	

};
