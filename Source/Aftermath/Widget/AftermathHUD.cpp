// Fill out your copyright notice in the Description page of Project Settings.

#include "AftermathHUD.h"
#include "Blueprint/UserWidget.h"       // for UUserWidget
#include "UMG.h"						// for UWidgetBlueprintLibrary


#include "AftermathUserWidget.h"
#include "OverlayWidgetController.h"


UOverlayWidgetController* AAftermathHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

void AAftermathHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
	UAttributeSet* AS)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("InitOverlay Called"));
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass not found, pleast fill out BP_HUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass not found, pleast fill out BP_HUD"));
	
	UUserWidget* Widget =  CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAftermathUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);
	
	// OverlayWidget->SetProgressBarPercentFunc();
	WidgetController->BroadcastInitialValues();
	WidgetController->BindCallBacksToDependencies();
	Widget->AddToViewport();
}
