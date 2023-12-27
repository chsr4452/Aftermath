// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AftermathHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UAftermathUserWidget;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AFTERMATH_API AAftermathHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UPROPERTY()
    TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
private:

	TObjectPtr<UAftermathUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere, Category = "OverlayWidget Setting")
	TSubclassOf<UAftermathUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "OverlayWidget Setting")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};