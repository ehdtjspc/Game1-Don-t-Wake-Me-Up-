// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "SpawnLocation.generated.h"

UCLASS()
class G1_API ASpawnLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetRandomPoint() const;

	FBox GetSpawnBox();

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<class UBoxComponent> SpawnBox;

	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;
};
