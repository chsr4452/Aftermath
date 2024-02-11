// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AftermathUserWidget.h"
#include "QuestionWidget.generated.h"

class UEditableTextBox;
/**
 * 
 */
UCLASS()
class AFTERMATH_API UQuestionWidget : public UAftermathUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditableTextBox* LeftBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditableTextBox* MiddleBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEditableTextBox* RightBox;

	UPROPERTY(EditAnywhere)
	FName TextVariable;
};
