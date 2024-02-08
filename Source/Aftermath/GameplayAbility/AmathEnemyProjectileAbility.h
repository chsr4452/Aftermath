// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmathGameplayAbilityBase.h"
#include "AmathEnemyProjectileAbility.generated.h"

/**
 * 
 */
class AAmathProjectile;
UCLASS()
class AFTERMATH_API UAmathEnemyProjectileAbility : public UAmathGameplayAbilityBase
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Blueprint Class")
	TSubclassOf<AAmathProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Effect Class")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay Effect Class")
	TSubclassOf<UGameplayEffect> EffectBurnClass;
};
