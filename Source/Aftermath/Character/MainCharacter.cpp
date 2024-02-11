// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "AbilitySystemComponent.h"
#include "Aftermath/GameplayAbility/AftermathAbilitySystemComponent.h"
#include "Aftermath/PlayerController/AftermathPlayerController.h"
#include "Aftermath/PlayerState/AftermathPlayerState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Aftermath/Widget/AftermathHUD.h"
#include "Aftermath/Widget/QuestionWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800;
	
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	Tags.Add(FName("Player"));

	QuestionBar = CreateDefaultSubobject<UWidgetComponent>("QuestionBar");
	QuestionBar->SetupAttachment(GetRootComponent());


}

void AMainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// UE_LOG(LogTemp, Warning, TEXT("Tick Function"));
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	FString const Equation = GenerateEquation();
	QuestionWidget= Cast<UQuestionWidget>(QuestionBar->GetUserWidgetObject());
	QuestionWidget->LeftBox->SetText(FText::FromString("Left From C++"));
	QuestionWidget->MiddleBox->SetText(FText::FromString(Equation));
	QuestionWidget->RightBox->SetText(FText::FromString("Right From C++"));
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilitySystemComponent();
	InitVitalAttributes();
	AddCharacterAbilities();
}

void AMainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilitySystemComponent();
}

int32 AMainCharacter::GetLevel()
{
	return 0;
}

void AMainCharacter::InitAbilitySystemComponent()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InitAbilitySystemComponent"));
	APlayerState * PlayerStateTemp = GetPlayerState();
	check(PlayerStateTemp)
	AAftermathPlayerState* AftermathPlayerState = Cast<AAftermathPlayerState>(PlayerStateTemp);
	// AAftermathPlayerState * AftermathPlayerState = GetPlayerState<AAftermathPlayerState>();
	check(AftermathPlayerState);
	AbilitySystemComponent = AftermathPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(AftermathPlayerState, this);
	AttributeSet = AftermathPlayerState->GetAttributeSet();
	
	if(AAftermathPlayerController* PC =  Cast<AAftermathPlayerController>(GetController()))
	{
		AAftermathHUD* HUD = PC->GetHUD<AAftermathHUD>();
		
		if(AAftermathHUD* AftermathHUD =  Cast<AAftermathHUD>(HUD))
		{
			AftermathHUD->InitOverlay(PC, AftermathPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	UAftermathAbilitySystemComponent* AftermathAbilitySystemComponent =  Cast<UAftermathAbilitySystemComponent>(AbilitySystemComponent);
	AftermathAbilitySystemComponent->AbilityActorInfoSet();
	
}

FString AMainCharacter::GenerateEquation()
{
	int32 a = FMath::RandRange(0, 10);
	int32 b = FMath::RandRange(1, 10); // Prevent divison by zero error
    
	TCHAR operators[] = { TEXT('+'), TEXT('-'), TEXT('*'), TEXT('/') };
	TCHAR randomOperator = operators[FMath::RandRange(0, 3)];
    
	switch(randomOperator) {
	case TEXT('+'):
		Answer = a + b;
		break;
	case TEXT('-'):
		Answer = a - b;
		break;
	case TEXT('*'):
		Answer = a * b;
		break;
	case TEXT('/'):
		Answer = a / b;
		break;
	default:
		Answer = 0;
		break;
	}
    
	return FString::Printf(TEXT("%d %c %d"), a, randomOperator, b);
}