// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathAttributeSet.h"

#include "Net/UnrealNetwork.h"

UAftermathAttributeSet::UAftermathAttributeSet()
{
	InitHealth(50);
	InitMaxHealth(100);
	InitMana(25);
	InitMaxMana(50);
}

void UAftermathAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAftermathAttributeSet, Health, OldHealth)
}

void UAftermathAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAftermathAttributeSet, MaxHealth, OldMaxHealth)
}


void UAftermathAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAftermathAttributeSet, Mana, OldMana)
}

void UAftermathAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAftermathAttributeSet, MaxMana, OldMaxMana)
}


void UAftermathAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAftermathAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAftermathAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAftermathAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAftermathAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

