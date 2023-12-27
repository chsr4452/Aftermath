// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathUserWidget.h"

void UAftermathUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
