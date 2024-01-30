// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmathGameplayAbilityBase.h"
#include "AmathProjectileAbility.generated.h"

class AAmathProjectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class AFTERMATH_API UAmathProjectileAbility : public UAmathGameplayAbilityBase
{
	GENERATED_BODY()
protected:

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Blueprint Class")
	TSubclassOf<AAmathProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Effect Class")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Effect Class")
	TSubclassOf<UGameplayEffect> EffectBurnClass;

	
};
