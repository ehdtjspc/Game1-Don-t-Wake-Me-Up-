// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "G1Define.h"
#include "GameplayTagContainer.h"
#include "G1PlayerController.generated.h"

struct FInputActionValue;
class UNiagaraSystem;

/**
 *
 */
UCLASS()
class G1_API AG1PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AG1PlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

public:
	virtual void HandleGameplayEvent(FGameplayTag EventTag);
	void TargetAttack();
	void TargetDontBotherMeSkill();
private:
	void TickCursorTrace();
	void ChaseTargetAndAttack();
private:
	
	void OnMoveStarted();
	void OnMoveTriggered();
	void OnMoveReleased();

	void OnAttackStarted();
	void OnAttackTriggered();
	void OnAttackReleased();

	void Input_Dash();
	void Input_DontBotherMe();

	ECreatureState GetCreatureState();
	void SetCreatureState(ECreatureState InState);



public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;



	
private:
	FVector CachedDestination;
	float FollowTime;
	bool bMousePressed = false;


protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Character> TargetActor;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Character> HighlightActor;


	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Player> G1Player;



	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> ActorsToIgnore;

	float AttackRange = 500.f;

	// 이펙트 설정 블루프린트로
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* NiagaraEffect; // NiagaraEffect 변수 선언

protected:
	FTimerHandle DashCooldownTimerHandle;  // 대쉬 쿨타임 타이머 핸들
	FTimerHandle DontBotherMeCooldownTimerHandle;
	void ResetDashCooldown();  // 쿨타임 끝나면 호출되는 함수
	void ResetDontBotherMeCooldown();

	bool bCanDash = true;
	bool bCanDontBotherMe = true;
	bool bCanDamaged = true;



	
};
