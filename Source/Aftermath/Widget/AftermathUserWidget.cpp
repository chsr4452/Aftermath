// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathUserWidget.h"

void UAftermathUserWidget::SetWidgetController(UObject* InInWidgetController)
{
	WidgetController = InInWidgetController;
	WidgetControllerSet();
}
