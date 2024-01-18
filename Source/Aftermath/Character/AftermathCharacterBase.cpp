// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathCharacterBase.h"

#include "Aftermath/GameplayAbility/AftermathAbilitySystemComponent.h"

// Sets default values
AAftermathCharacterBase::AAftermathCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* AAftermathCharacterBase::GetAbilitySystemComponent() const
{return AbilitySystemComponent;
}

void AAftermathCharacterBase::AddCharacterAbilities()
{
	UAftermathAbilitySystemComponent* AmathASC = CastChecked<UAftermathAbilitySystemComponent>(AbilitySystemComponent);
	if(!HasAuthority()) return;

	AmathASC->AddCharacterAbilities(StartupAbilities);
}

void AAftermathCharacterBase::InitVitalAttributes()
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultVitalAttributes);
	const FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle const EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultVitalAttributes, 1.f, EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}

FVector AAftermathCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}



