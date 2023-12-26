// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AftermathHUD.generated.h"

class UAftermathUserWidget;
/**
 * 
 */
UCLASS()
class AFTERMATH_API AAftermathHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	TObjectPtr<UAftermathUserWidget> OverlayWidget;
	
private:
	UPROPERTY(EditAnywhere, Category = "OverlayWidget Setting")
	TSubclassOf<UAftermathUserWidget> OverlayWidgetClass;
	
};