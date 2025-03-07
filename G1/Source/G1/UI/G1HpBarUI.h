// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "G1HpBarUI.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1HpBarUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UG1HpBarUI(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;  //Tick 같은 함수

public:
	void SetHpRatio(float Ratio);


protected:

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UProgressBar> HpBar;
	
};
