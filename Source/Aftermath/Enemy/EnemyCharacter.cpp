// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "Aftermath/AI/AIController_Enemy.h"
#include "Aftermath/GameplayAbility/AftermathAbilitySystemComponent.h"
#include "Aftermath/GameplayAbility/AftermathAttributeSet.h"
#include "Aftermath/GameplayAbility/AmathProjectileAbility.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAftermathAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAftermathAttributeSet>("AttributeSet");
	AmathAttributeSet = CastChecked<UAftermathAttributeSet>(AttributeSet);
	
	AmathAttributeSet->InitHealth(100);
	AmathAttributeSet->InitMaxHealth(100);
	AmathAttributeSet->InitMana(100);
	AmathAttributeSet->InitMaxMana(100);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	Tags.Add(FName("Enemy"));
	// AttackAbility = UAmathEnemyProjectileAbility::StaticClass();
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if(UAftermathUserWidget* AmathUserWidget = Cast<UAftermathUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AmathUserWidget->SetWidgetController(this);
	}
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AmathAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChange);

	OnHealthChange.Broadcast(AmathAttributeSet->GetHealth());
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(!HasAuthority()) return;
	AIController_Enemy = Cast<AAIController_Enemy>(NewController);
	AIController_Enemy->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AIController_Enemy->RunBehaviorTree(BehaviorTree);
}

void AEnemyCharacter::Die()
{
	Super::Die();
}

void AEnemyCharacter::HealthChange(const FOnAttributeChangeData& Data)
{
	// GetCharacterMovement()->StopMovementImmediately();
	// PlayAnimMontage(HitReactMontage);
	OnHealthChange.Broadcast(Data.NewValue);
	if(Data.NewValue <= 0)
	{
		SetLifeSpan(LifeSpan);
		Die();
	}
}

void AEnemyCharacter::EnemyAttack()
{
	if(AbilitySystemComponent)
	{	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Enemy Attack Activated.");
		FGameplayAbilitySpec const Spec(AttackAbility, 1, 0);
		auto ActivatableAbilitiesArray1 =  this->AbilitySystemComponent->GetActivatableAbilities();
		this->AbilitySystemComponent->GiveAbility(Spec);
		auto ActivatableAbilitiesArray2 =  this->AbilitySystemComponent->GetActivatableAbilities();
		AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}
