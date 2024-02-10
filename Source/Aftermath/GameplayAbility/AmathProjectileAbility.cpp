// Fill out your copyright notice in the Description page of Project Settings.


#include "AmathProjectileAbility.h"

#include "Aftermath/Character/MainCharacter.h"
#include "Aftermath/EffectActor/AmathProjectile.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UAmathProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// UKismetSystemLibrary::PrintString(this, FString("Activate Ability (C++)"), true, true, FColor::Red, 5);
	
	const bool HasAuth = HasAuthority(&ActivationInfo);
	if(!HasAuth) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if(CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(GetAvatarActorFromActorInfo()->GetActorRotation().Quaternion());
       	AAmathProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAmathProjectile>(
        		ProjectileClass,
        		SpawnTransform,
        		GetOwningActorFromActorInfo(),
        		Cast<APawn>(GetOwningActorFromActorInfo()),
        		ESpawnActorCollisionHandlingMethod::AlwaysSpawn,
        		ESpawnActorScaleMethod::MultiplyWithRoot
        		);
			
			// Projectile->SetActorRotation(GetAvatarActorFromActorInfo()->GetActorRotation());
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
}
