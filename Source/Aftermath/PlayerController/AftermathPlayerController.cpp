// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AAftermathPlayerController::AAftermathPlayerController()
{
}

void AAftermathPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(InputMappingContext,0);

	// bShowMouseCursor = true;
	// DefaultMouseCursor = EMouseCursor::Default;
	
	// FInputModeGameAndUI InputModeData;
	// InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// InputModeData.SetHideCursorDuringCapture(true);
	// SetInputMode(InputModeData);
}

void AAftermathPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	EnhancedInputComponent =  Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &AAftermathPlayerController::Move);
}

void AAftermathPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FVector NorthDirection = FVector(1, 0, 0);
	const FVector EastDirection = FVector(0, 1, 0);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(NorthDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(EastDirection, InputAxisVector.X);
	}
}
