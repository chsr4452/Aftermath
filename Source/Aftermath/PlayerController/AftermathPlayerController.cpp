// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathPlayerController.h"
#include "../Input/AmathInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Aftermath/GameplayAbility/AftermathAbilitySystemComponent.h"

AAftermathPlayerController::AAftermathPlayerController()
{
}

void AAftermathPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext,0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(true);
	SetInputMode(InputModeData);
}

void AAftermathPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	AmathInputComponent=  Cast<UAmathInputComponent>(InputComponent);
	AmathInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &AAftermathPlayerController::Move);
	AmathInputComponent->BindAbilityActions(InputConfig, this, &AAftermathPlayerController::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
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

void AAftermathPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void AAftermathPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(GetASC() == nullptr) return;
	
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AAftermathPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(GetASC() == nullptr) return;
	
	GetASC()->AbilityInputTagHeld(InputTag);
}

UAftermathAbilitySystemComponent* AAftermathPlayerController::GetASC()
{
	if(AftermathAbilitySystemComponent == nullptr)
	{
		AftermathAbilitySystemComponent = Cast<UAftermathAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AftermathAbilitySystemComponent;
}
