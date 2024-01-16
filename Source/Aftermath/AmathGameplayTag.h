// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
/**
 * 
 */

struct FAmathGameplayTags
{
public:
 static const FAmathGameplayTags& Get(){return GameplayTags;}
 static void InitNativeGameplayTags();
 FGameplayTag Attributes_Secondary_Armor;
 FGameplayTag Attributes_Vital_Health;
 FGameplayTag Attributes_Vital_Mana;
 FGameplayTag Attributes_Vital_MaxHealth;
 FGameplayTag Attributes_Vital_MaxMana;
 FGameplayTag InputTag_LMB;
 FGameplayTag InputTag_RMB;
 

 
protected:
 
private:
 static FAmathGameplayTags GameplayTags;
 
};