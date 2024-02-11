// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathAbilitySystemComponent.h"

#include "AmathGameplayAbilityBase.h"
#include "Aftermath/Character/AftermathCharacterBase.h"
#include "Aftermath/Character/MainCharacter.h"
#include "Aftermath/Misc/AmathGameplayTag.h"
#include "Aftermath/Widget/QuestionWidget.h"
#include "Components/EditableTextBox.h"

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

				//Update Question Widget
				AMainCharacter* MainCharacter= Cast<AMainCharacter>(Avatar);
				FString NewEquation = MainCharacter->GenerateEquation();
				MainCharacter->Answer;
				MainCharacter->QuestionWidget->LeftBox->SetText(FText::AsNumber(MainCharacter->Answer));
				MainCharacter->QuestionWidget->MiddleBox->SetText(FText::FromString(NewEquation));
				MainCharacter->QuestionWidget->RightBox->SetText(FText::AsNumber(MainCharacter->Answer));
				
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
