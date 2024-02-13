// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AftermathCharacterBase.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

#include "MainCharacter.generated.h"

class AAftermathPlayerController;
class UQuestionWidget;
class UEditableTextBox;
class UAftermathUserWidget;
class UWidgetComponent;
class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */

// USTRUCT()
// struct FQuestionStruct
// {
// 	GENERATED_BODY()
//
// 	FQuestionStruct(){}
// 	TArray<FName> InputTagList = {FName("InputTag.LMB"), FName("InputTag.RMB")};
// 	TArray<int> AnswerList;
// 	FString* Question = nullptr;
// };

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
	
	UFUNCTION()
	virtual void GenerateEquation();

	
protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY()
	TObjectPtr<USpringArmComponent> SpringArm;

	void InitAbilitySystemComponent();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> QuestionBar;

	TArray<FName> InputTagList = {FName("InputTag.LMB"), FName("InputTag.RMB")};

	TObjectPtr<AAftermathPlayerController> PC;
	
public:
	int RightAnswer{0};
	int WrongAnswer{0};
	FName CorrectTag;
	TArray<int> AnswerList= {RightAnswer, WrongAnswer};
	FString Equation;

	void CharacterStunt();
	void EndOfStunt();
};

