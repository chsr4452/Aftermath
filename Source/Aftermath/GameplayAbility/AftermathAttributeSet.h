// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AftermathAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, AttributeName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, AttributeName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(AttributeName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(AttributeName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(AttributeName)

// struct FGameplayEffectContextHandle;

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}
	
	UPROPERTY()
    FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC;

	UPROPERTY()
	TObjectPtr<AActor> TargetActor;

	UPROPERTY()
	TObjectPtr<AController> TargetController;

	UPROPERTY()
	TObjectPtr<ACharacter> TargetCharacter;



	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor;

	UPROPERTY()
	TObjectPtr<AController> SourceController;

	UPROPERTY()
	TObjectPtr<ACharacter> SourceCharacter;


};



UCLASS()
class AFTERMATH_API UAftermathAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAftermathAttributeSet();

	FEffectProperties* PropPtr;
	
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
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
