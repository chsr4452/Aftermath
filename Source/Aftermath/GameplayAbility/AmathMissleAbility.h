// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmathGameplayAbilityBase.h"
#include "AmathMissleAbility.generated.h"

class AAmathMissle;
/**
 * 
 */
UCLASS()
class AFTERMATH_API UAmathMissleAbility : public UAmathGameplayAbilityBase
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAmathMissle> Missle;
};
