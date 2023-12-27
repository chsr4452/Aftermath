// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlayWidgetController.h"
#include "Aftermath/GameplayAbility/AftermathAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAftermathAttributeSet* AftermathAttributeSet = Cast<UAftermathAttributeSet>(AttributeSet);
	
	OnHealthChange.Broadcast(AftermathAttributeSet->GetHealth());
	OnMaxHealthChange.Broadcast(AftermathAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallBacksToDependencies()
{
	const UAftermathAttributeSet* AftermathAttributeSet = Cast<UAftermathAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AftermathAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AftermathAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChange.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChange.Broadcast(Data.NewValue);
}
