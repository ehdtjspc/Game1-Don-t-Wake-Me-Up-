// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "G1ObjectAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)			\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)	\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)				\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)				\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class G1_API UG1ObjectAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UG1ObjectAttributeSet();

public:
	ATTRIBUTE_ACCESSORS(ThisClass, Hp);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHp);

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))// private 일때 meta = (AllowPrivateAccess = "true") 이걸 사용 하면 블루프린트에서 에러가 안난다.
	FGameplayAttributeData Hp;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHp;



	
};
