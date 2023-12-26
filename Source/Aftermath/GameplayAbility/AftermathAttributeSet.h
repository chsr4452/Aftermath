// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AftermathAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, AttributeName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, AttributeName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(AttributeName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(AttributeName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(AttributeName)

UCLASS()
class AFTERMATH_API UAftermathAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAftermathAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health);
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAftermathAttributeSet,  Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth);
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAftermathAttributeSet,  MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

		
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Mana);
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAftermathAttributeSet,  Mana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxMana);
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAftermathAttributeSet,  MaxMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
