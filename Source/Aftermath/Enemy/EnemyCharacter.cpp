// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "Aftermath/GameplayAbility/AftermathAbilitySystemComponent.h"
#include "Aftermath/GameplayAbility/AftermathAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAftermathAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	
	
	AttributeSet = CreateDefaultSubobject<UAftermathAttributeSet>("AttributeSet");
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
}
