// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1AnimNotify_SendGameplayEvent.h"
#include "Character/G1Character.h"

UG1AnimNotify_SendGameplayEvent::UG1AnimNotify_SendGameplayEvent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UG1AnimNotify_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AG1Character* LocalCharacter = Cast<AG1Character>(MeshComp->GetOwner());
	
	if (LocalCharacter)
	{
		LocalCharacter->HandleGameplayEvent(EventTag);
	}

}
