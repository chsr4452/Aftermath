// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "AbilitySystemComponent.h"
#include "NavigationSystemTypes.h"
#include "Aftermath/GameplayAbility/AftermathAbilitySystemComponent.h"
#include "Aftermath/PlayerController/AftermathPlayerController.h"
#include "Aftermath/PlayerState/AftermathPlayerState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Aftermath/Widget/AftermathHUD.h"

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
	
}

void AMainCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// UE_LOG(LogTemp, Warning, TEXT("Tick Function"));
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilitySystemComponent();
	AddCharacterAbilities();
}

void AMainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilitySystemComponent();
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
