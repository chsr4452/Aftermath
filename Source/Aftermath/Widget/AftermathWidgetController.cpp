// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathWidgetController.h"

void UAftermathWidgetController::BroadcastInitialValues()
{
}

void UAftermathWidgetController::BindCallBacksToDependencies()
{
}

void UAftermathWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

