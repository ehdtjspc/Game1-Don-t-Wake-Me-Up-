// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1AnimNotify_Die.h"
#include "Character/G1Character.h"

UG1AnimNotify_Die::UG1AnimNotify_Die(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{

}

void UG1AnimNotify_Die::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	
	AG1Character* LocalCharacter = Cast<AG1Character>(MeshComp->GetOwner());

	if (LocalCharacter)
	{
		LocalCharacter->Destroy();

	}

}
