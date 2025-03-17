// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1AnimNotify_DontBotherMe.h"
#include "G1AnimNotify_DontBotherMe.h"
#include "Character/G1Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


UG1AnimNotify_DontBotherMe::UG1AnimNotify_DontBotherMe()
{

}

void UG1AnimNotify_DontBotherMe::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
   
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, TEXT("SSSSSS"));

    AG1Character* LocalCharacter = Cast<AG1Character>(MeshComp->GetOwner());

	if (LocalCharacter)
	{
		LocalCharacter->HandleGameplayEvent(EventTag);

	}
 


}
