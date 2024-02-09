// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"

#include "Aftermath/Character/MainCharacter.h"
#include "Aftermath/GameplayAbility/AftermathAbilitySystemComponent.h"
#include "Aftermath/GameplayAbility/AftermathAttributeSet.h"



void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAftermathAttributeSet* AftermathAttributeSet = Cast<UAftermathAttributeSet>(AttributeSet);
	OnHealthChange.Broadcast(AftermathAttributeSet->GetHealth());
	OnMaxHealthChange.Broadcast(AftermathAttributeSet->GetMaxHealth());
	
	OnManaChange.Broadcast(AftermathAttributeSet->GetMana());
	OnMaxManaChange.Broadcast(AftermathAttributeSet->GetMaxMana());
	
}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BindCallBacksToDependencies"));
	const UAftermathAttributeSet* AftermathAttributeSet = Cast<UAftermathAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AftermathAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AftermathAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AftermathAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AftermathAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	UAftermathAbilitySystemComponent* AftermathAbilitySystemComponent = Cast<UAftermathAbilitySystemComponent>(AbilitySystemComponent);
	AftermathAbilitySystemComponent->OnGetTag.AddLambda([this](const FGameplayTagContainer& AssetTag)
	{
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Lambda called"));
		for(const FGameplayTag& Tag:AssetTag)
		{
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("For loop called"));
			FGameplayTag MessageTag =  FGameplayTag::RequestGameplayTag(FName("Message"));
			
			
			// const FString Msg = FString::Printf(TEXT("Tag Name: %s"), *Tag.ToString());
			// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Msg);

			if(Tag.MatchesTag(MessageTag))
			{
				checkf(MessageWidgetDatatable, TEXT("Where is the MessageWidgetDataTable Dude?"));
				FTagDataTable* Row = MessageWidgetDatatable->FindRow<FTagDataTable>(Tag.GetTagName(), TEXT("ContextString"));
				OnGetRowName.Broadcast(*Row);
			}
		}
	});
}

float UOverlayWidgetController::GetHealthFloat(float NewValue) const
{
	return NewValue;
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChange.Broadcast(Data.NewValue);
	if(Data.NewValue <= 0) Cast<AMainCharacter>(PlayerController->GetCharacter())->Die();
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChange.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChange.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChange.Broadcast(Data.NewValue);
}

