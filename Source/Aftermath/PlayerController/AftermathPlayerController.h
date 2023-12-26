// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AftermathPlayerController.generated.h"

/**
 */

class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;
struct FInputActionValue;

UCLASS
()
class AFTERMATH_API AAftermathPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAftermathPlayerController();
	virtual void BeginPlay() override;
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

private:
	
	virtual void SetupInputComponent() override;
	
	virtual void Move(const FInputActionValue& InputActionValue);
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ActionMove;

	
};
