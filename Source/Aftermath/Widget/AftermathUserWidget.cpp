// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathUserWidget.h"

#include "Components/ProgressBar.h"

void UAftermathUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

// void UAftermathUserWidget::SetProgressBarPercentFunc()
// {
// 	ProgressBar->SetPercent(0.1);
// }
