// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpawnManager.generated.h"



UCLASS()
class G1_API ASpawnManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
	void SpawnMonster();


	//몬스터 클래스 (어떤 몬스터를 소환할지 지정)
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AG1Monster> MonsterClass;


	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	TArray<FVector> SpawnLocations;

};
