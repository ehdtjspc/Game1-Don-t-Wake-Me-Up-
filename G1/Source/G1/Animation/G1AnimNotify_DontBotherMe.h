// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotify_PlayNiagaraEffect.h"
#include "GameplayTagContainer.h"
#include "G1AnimNotify_DontBotherMe.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1AnimNotify_DontBotherMe : public UAnimNotify_PlayNiagaraEffect
{
	GENERATED_BODY()
	
public:
	UG1AnimNotify_DontBotherMe();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;

};
