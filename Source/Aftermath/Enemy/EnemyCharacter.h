// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aftermath/Character/AftermathCharacterBase.h"
#include "../Widget/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

class UAftermathAttributeSet;
class FOnHealthChangeSignature;
class AAIController_Enemy;
class UBehaviorTree;
/**
 * 
 */
class UWidgetComponent;
UCLASS()
class AFTERMATH_API AEnemyCharacter : public AAftermathCharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChange;

	virtual void Die() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;
	
	//
	// UPROPERTY(EditAnywhere, Category = Animation)
	// UAnimMontage* HitReactMontage;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY()
	UAftermathAttributeSet* AmathAttributeSet;

	
	void HealthChange(const FOnAttributeChangeData& Data);

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAIController_Enemy> AIController_Enemy;
};
