// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AftermathPlayerController.generated.h"

/**
 */

struct FGameplayTag;
class UInputConfigDataAsset;
class UInputMappingContext;
class UInputAction;
class UAmathInputComponent;
struct FInputActionValue;
class UAftermathAbilitySystemComponent;

UCLASS
()
class AFTERMATH_API AAftermathPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAftermathPlayerController();
	virtual void BeginPlay() override;
	TObjectPtr<UAmathInputComponent> AmathInputComponent;

private:
	
	virtual void SetupInputComponent() override;
	
	virtual void Move(const FInputActionValue& InputActionValue);
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ActionMove;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputConfigDataAsset> InputConfig;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY()
	TObjectPtr<UAftermathAbilitySystemComponent> AftermathAbilitySystemComponent;

	UAftermathAbilitySystemComponent* GetASC();
};
