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
	
	QuestionWidget= Cast<UQuestionWidget>(QuestionBar->GetUserWidgetObject());
	GenerateEquation();
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

void AMainCharacter::GenerateEquation()
{
	int32 a = FMath::RandRange(0, 10);
	int32 b = FMath::RandRange(1, 10); // Prevent divison by zero error
    
	TCHAR operators[] = { TEXT('+'), TEXT('-'), TEXT('*'), TEXT('/') };
	TCHAR randomOperator = operators[FMath::RandRange(0, 3)];
    
	switch(randomOperator) {
	case TEXT('+'):
		RightAnswer = a + b;
		break;
	case TEXT('-'):
		RightAnswer = a - b;
		break;
	case TEXT('*'):
		RightAnswer = a * b;
		break;
	case TEXT('/'):
		a *= b;
		RightAnswer = a / b;
		break;
	default:
		RightAnswer = 0;
		break;
	}
	WrongAnswer = RightAnswer + FMath::RandRange(1, 20);

	int RandomZeroOrOne = FMath::RandBool() ? 1 : 0;
	if(RandomZeroOrOne)
	{
		AnswerList = {RightAnswer, WrongAnswer};
		CorrectTag = InputTagList[0];
	}
	else
	{
		AnswerList = {WrongAnswer, RightAnswer};
		CorrectTag = InputTagList[1];
	}
	
	Equation = FString::Printf(TEXT("%d %c %d"), a, randomOperator, b);
	
	if(CorrectTag == FName("InputTag.LMB"))
	{
		QuestionWidget->LeftBox->SetText(FText::AsNumber(RightAnswer));
		QuestionWidget->MiddleBox->SetText(FText::FromString(Equation));
		QuestionWidget->RightBox->SetText(FText::AsNumber(WrongAnswer));
						
	}
	else
	{
		QuestionWidget->LeftBox->SetText(FText::AsNumber(WrongAnswer));
		QuestionWidget->MiddleBox->SetText(FText::FromString(Equation));
		QuestionWidget->RightBox->SetText(FText::AsNumber(RightAnswer));
	}
}