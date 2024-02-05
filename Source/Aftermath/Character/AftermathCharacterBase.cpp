// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathCharacterBase.h"

#include "Aftermath/GameplayAbility/AftermathAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAftermathCharacterBase::AAftermathCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAftermathCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	Tags.AddUnique(Tag);
	Tags.AddUnique(AttackType);
}

UAbilitySystemComponent* AAftermathCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAftermathCharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetAnimationMode(EAnimationMode::Type::AnimationCustomMode);
	// GetMesh()->SetAllBodiesSimulatePhysics(true);
	// GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	// GetCharacterMovement()->SetComponentTickEnabled(false);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAftermathCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	GetMesh()->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

void AAftermathCharacterBase::AddCharacterAbilities()
{
	UAftermathAbilitySystemComponent* AmathASC = CastChecked<UAftermathAbilitySystemComponent>(AbilitySystemComponent);
	if(!HasAuthority()) return;
	AmathASC->AddCharacterAbilities(StartupAbilities);
}

void AAftermathCharacterBase::InitVitalAttributes()
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultVitalAttributes);
	const FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle const EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultVitalAttributes, 1.f, EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}

FVector AAftermathCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}



