// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/G1HpBarUI.h"
#include "Components/ProgressBar.h"

UG1HpBarUI::UG1HpBarUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UG1HpBarUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UG1HpBarUI::SetHpRatio(float Ratio)
{
	if (HpBar)
	{
		HpBar->SetPercent(Ratio);
	}
}
