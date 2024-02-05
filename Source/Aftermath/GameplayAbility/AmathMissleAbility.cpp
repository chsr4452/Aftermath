// Fill out your copyright notice in the Description page of Project Settings.


#include "AmathMissleAbility.h"

#include "Aftermath/EffectActor/AmathMissle.h"

void UAmathMissleAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FVector MissleLocation = FVector(0.f, 0.f, 0.f);
	FRotator MissleRotator = FRotator(0.f, 0.f, 0.f);
	
	AActor* MissleActor = GetWorld()->SpawnActor<AAmathMissle>(Missle, MissleLocation, MissleRotator);
}
