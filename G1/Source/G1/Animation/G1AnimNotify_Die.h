// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "G1AnimNotify_Die.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1AnimNotify_Die : public UAnimNotify
{
	GENERATED_BODY()

public:
	UG1AnimNotify_Die(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;
};
