// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathPlayerState.h"

#include "Aftermath/GameplayAbility/AftermathAbilitySystemComponent.h"
#include "Aftermath/GameplayAbility/AftermathAttributeSet.h"


AAftermathPlayerState::AAftermathPlayerState()
{	NetUpdateFrequency = 100.f;
	AbilitySystemComponent = CreateDefaultSubobject<UAftermathAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UAftermathAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AAftermathPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

