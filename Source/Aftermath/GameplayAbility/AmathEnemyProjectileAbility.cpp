// Fill out your copyright notice in the Description page of Project Settings.


#include "AmathEnemyProjectileAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Aftermath/Character/AftermathCharacterBase.h"
#include "Aftermath/EffectActor/AmathProjectile.h"

void UAmathEnemyProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	const bool HasAuth = HasAuthority(&ActivationInfo);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, "EnemyAttackAbility");
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetOwningActorFromActorInfo()->GetActorLocation());
	SpawnTransform.SetRotation(GetAvatarActorFromActorInfo()->GetActorRotation().Quaternion());
	AAmathProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAmathProjectile>(
		 ProjectileClass,
		 SpawnTransform,
		 GetOwningActorFromActorInfo(),
		 Cast<APawn>(GetOwningActorFromActorInfo()),
		 ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
		 ESpawnActorScaleMethod::MultiplyWithRoot
		 );

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	if(HasAuth)
	{
		const FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, 1, EffectContextHandle);
		const FGameplayEffectSpecHandle SpecHandleBurn = SourceASC->MakeOutgoingSpec(EffectBurnClass, 1, EffectContextHandle);
		Projectile->DamageEffectSpecHandle = SpecHandle;
		Projectile->EffectBurnSpecHandle = SpecHandleBurn;
		Projectile->FinishSpawning(SpawnTransform);
	}
}
