// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AftermathPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AFTERMATH_API AAftermathPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:

	AAftermathPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent()  const override;
	virtual UAttributeSet* GetAttributeSet()const {return AttributeSet;}
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
