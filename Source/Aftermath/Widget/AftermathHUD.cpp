// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathHUD.h"

#include "AftermathUserWidget.h"

void AAftermathHUD::BeginPlay()
{
	Super::BeginPlay();

	UAftermathUserWidget* Widget =  CreateWidget<UAftermathUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
