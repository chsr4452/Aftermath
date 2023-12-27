// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathHUD.h"

#include "AftermathUserWidget.h"
#include "OverlayWidgetController.h"


UOverlayWidgetController* AAftermathHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallBacksToDependencies();
		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

void AAftermathHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
	UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass not found, pleast fill out BP_HUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass not found, pleast fill out BP_HUD"));
	
	UUserWidget* Widget =  CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAftermathUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	// WidgetController->BindCallBacksToDependencies();
	OverlayWidget->AddToViewport();
}
