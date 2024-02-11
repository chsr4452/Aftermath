// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AftermathCharacterBase.h"
#include "MainCharacter.generated.h"

class UQuestionWidget;
class UEditableTextBox;
class UAftermathUserWidget;
class UWidgetComponent;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AFTERMATH_API AMainCharacter : public AAftermathCharacterBase
{
	GENERATED_BODY()
public:
	AMainCharacter();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual int32 GetLevel() override;

	UPROPERTY()
	TObjectPtr<UAftermathUserWidget> WidgetInComponent;
	TObjectPtr<UQuestionWidget> QuestionWidget;


	
protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArm;

	void InitAbilitySystemComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> QuestionBar;

	virtual FString GenerateEquation();

	int Answer{0};
	
	
};

