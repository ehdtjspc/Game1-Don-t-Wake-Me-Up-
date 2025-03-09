// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "G1Define.h"
#include "Components/WidgetComponent.h"
#include "UI/G1HpBarUI.h"
#include "AbilitySystem/G1AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/G1AttributeSet.h"


// Sets default values
AG1Character::AG1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HpBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HpBarComponent->SetupAttachment(GetRootComponent());

	ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (HealthBarWidgetClass.Succeeded())
	{
		HpBarComponent->SetWidgetClass(HealthBarWidgetClass.Class);
		HpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarComponent->SetDrawAtDesiredSize(true);
		HpBarComponent->SetRelativeLocation(FVector(0, 0, 110));
	}

}

// Called when the game starts or when spawned
void AG1Character::BeginPlay()
{
	Super::BeginPlay();
	RefreshHpBarRatio();

	AddCharacterAbilities();
}

// Called every frame
void AG1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AG1Character::HandleGameplayEvent(FGameplayTag EventTag)
{

}

// Called to bind functionality to input
void AG1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AG1Character::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AG1Character::UnHighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void AG1Character::OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker)
{
	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	AttributeSet->SetHealth(Hp);

	if (Hp == 0)
	{
		OnDead(Attacker);
	}

	//D(FString::Printf(TEXT("%d"), Hp));
	RefreshHpBarRatio();


}

void AG1Character::OnDead(TObjectPtr<AG1Character> Attacker)
{
	if (CreatureState == ECreatureState::Dead)
	{
		CreatureState = ECreatureState::Dead;
	}
}

void AG1Character::RefreshHpBarRatio()
{
	if (HpBarComponent && AttributeSet)
	{
		float Hp = AttributeSet->GetHealth();
		float MaxHp = AttributeSet->GetMaxHealth();

		float Ratio = static_cast<float>(Hp) / MaxHp;
		UG1HpBarUI* HpBar =Cast<UG1HpBarUI>(HpBarComponent->GetUserWidgetObject());
		HpBar->SetHpRatio(Ratio);
	}
}

UAbilitySystemComponent* AG1Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AG1Character::InitAbilitySystem()
{

}

void AG1Character::AddCharacterAbilities()
{
	UG1AbilitySystemComponent* ASC =Cast<UG1AbilitySystemComponent>(AbilitySystemComponent);
	if (ASC == nullptr)
	{
		return;
	}

	ASC->AddCharacterAbilities(StartupAbilities);
}

