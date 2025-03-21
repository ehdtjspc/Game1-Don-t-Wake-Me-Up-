

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpawnAllLocation.generated.h"

UCLASS()
class G1_API ASpawnAllLocation : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpawnAllLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FVector GetSpawnLocation1();
	FVector GetSpawnLocation2();
	FVector GetSpawnLocation3();
	FVector GetSpawnLocation4();



private:

	// 스폰 지역 찾기 사용가능한
	void FindSpawnAreas();
	

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn")
	TArray<class ASpawnLocation*> SpawnLocations;
 



};
