// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmathGameplayAbilityBase.h"
#include "AmathProjectileAbility.generated.h"

/**
 * 
 */
UCLASS()
class AFTERMATH_API UAmathProjectileAbility : public UAmathGameplayAbilityBase
{
	GENERATED_BODY()
protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
