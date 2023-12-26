// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aftermath/Character/AftermathCharacterBase.h"

#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AFTERMATH_API AEnemyCharacter : public AAftermathCharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void BeginPlay() override;
	
	
};
