// Fill out your copyright notice in the Description page of Project Settings.


#include "AmathAssetManager.h"
#include "Misc/AmathGameplayTag.h"

UAmathAssetManager& UAmathAssetManager::Get()
{
	check(GEngine);
	UAmathAssetManager* AmathAssetManager = Cast<UAmathAssetManager>(GEngine->AssetManager);
	return *AmathAssetManager;
}

void UAmathAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAmathGameplayTags::InitNativeGameplayTags();
}
