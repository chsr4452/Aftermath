// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmathGameplayAbilityBase.h"
#include "DOTAbility.generated.h"

/**
 * 
 */
UCLASS()
class AFTERMATH_API UDOTAbility : public UAmathGameplayAbilityBase
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
