// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathAbilitySystemComponent.h"

#include "AmathGameplayAbilityBase.h"
#include "Aftermath/Character/AftermathCharacterBase.h"
#include "Aftermath/Character/MainCharacter.h"
#include "Aftermath/Misc/AmathGameplayTag.h"

void UAftermathAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAftermathAbilitySystemComponent::EffectAppliedToSelf);
}

void UAftermathAbilitySystemComponent::EffectAppliedToSelf(UAbilitySystemComponent* Source,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
		FGameplayTagContainer TagContainer;
    	SpecApplied.GetAllAssetTags(TagContainer);
		OnGetTag.Broadcast(TagContainer);
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EffectAppliedToSelf Called"));
}

void UAftermathAbilitySystemComponent::AddCharacterAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for(const TSubclassOf<UGameplayAbility> AbilityClass:StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if(const UAmathGameplayAbilityBase* AmathGameplayAbilityBase = Cast<UAmathGameplayAbilityBase>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AmathGameplayAbilityBase->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UAftermathAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;
	for(auto& AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
		AbilitySpecInputPressed(AbilitySpec);
			if(!AbilitySpec.IsActive())
			{	AActor* Avatar = this->GetAvatarActor();
				AMainCharacter* MainCharacter= Cast<AMainCharacter>(Avatar);
				
				if(MainCharacter->IsDead) return;
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAftermathAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;
	for(auto& AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}
