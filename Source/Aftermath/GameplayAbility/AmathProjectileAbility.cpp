// Fill out your copyright notice in the Description page of Project Settings.


#include "AmathProjectileAbility.h"
#include "Kismet/KismetSystemLibrary.h"

void UAmathProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UKismetSystemLibrary::PrintString(this, FString("Activate Ability (C++)"), true, true, FColor::Red, 5);
}
