// Fill out your copyright notice in the Description page of Project Settings.


#include "AmathGameplayTag.h"
#include "GameplayTagsManager.h"

FAmathGameplayTags FAmathGameplayTags::GameplayTags;

void FAmathGameplayTags::InitNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Reduce damage taken."));
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"),FString("Current Hit Point."));
	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"),FString("Current Magic Point."));
	GameplayTags.Attributes_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxHealth"),FString("Current Max Hit Point."));
	GameplayTags.Attributes_Vital_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.MaxMana"),FString("Current Max Magic Point."));
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),FString("Left Mouse Button."));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString("Right Mouse Button."));

	// GameplayTags.Message_HealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthPotion"),FString("Health Potion"));
	// GameplayTags.Message_HealthCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthCrystal"),FString("Health Crystal"));
	// GameplayTags.Message_ManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaPotion"),FString("Mana Potion"));
	// GameplayTags.Message_ManaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaCrystal"),FString("Mana Crystal"));


}
