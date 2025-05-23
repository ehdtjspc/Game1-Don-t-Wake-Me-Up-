// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "G1HighlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UG1HighlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class G1_API IG1HighlightInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Highlight() = 0;        //순수 가상 함수
	virtual void UnHighlight() = 0;       //순수 가상 함수
};
