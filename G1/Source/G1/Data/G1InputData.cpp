// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/G1InputData.h"


const UInputAction* UG1InputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FG1InputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for InputTag [%s]"), *InputTag.ToString());


	return nullptr;
}
