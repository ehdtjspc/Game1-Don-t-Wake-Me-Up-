// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1AnimNotify_SendGameplayEvent.h"
#include "Character/Player/G1Player.h"
#include "Character/Monster/G1Monster.h"

UG1AnimNotify_SendGameplayEvent::UG1AnimNotify_SendGameplayEvent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UG1AnimNotify_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AG1Player* LocalCharacter = Cast<AG1Player>(MeshComp->GetOwner());
	AG1Monster* LocalMonster = Cast<AG1Monster>(MeshComp->GetOwner());



	if (LocalCharacter)
	{
		LocalCharacter->HandleGameplayEvent(EventTag);
	}

	if (LocalMonster)
	{
		LocalMonster->HandleGameplayEvent(EventTag);
	}
}

