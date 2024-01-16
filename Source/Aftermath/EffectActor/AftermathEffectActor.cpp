// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

#include "AbilitySystemInterface.h"
#include "EditorDirectories.h"
#include "Aftermath/GameplayAbility/AftermathAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAftermathEffectActor::AAftermathEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>("ActorMesh");
	SetRootComponent(ActorMesh);
	
	// ActorSphere = CreateDefaultSubobject<USphereComponent>("ActorSphere");
	// ActorSphere->SetupAttachment(RootComponent);
}


void AAftermathEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if(InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectOnTarget(TargetActor, InstantEffectClass);
	}
	
	if(DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectOnTarget(TargetActor, DurationEffectClass);
	}
	
	if(InfiniteApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectOnTarget(TargetActor, InfiniteEffectClass);
	}
}

void AAftermathEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if(InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectOnTarget(TargetActor, InstantEffectClass);
	}
	
	if(DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectOnTarget(TargetActor, DurationEffectClass);
	}
	
	if(InfiniteApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectOnTarget(TargetActor, InfiniteEffectClass);
	}
	
	if(InfiniteRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(TargetASC == nullptr) return;
		TArray<FActiveGameplayEffectHandle> HandleToRemove;
		for(auto Handle: ActiveGameplayEffects)
		{
			if(Handle.Value == TargetASC)
			{
				TargetASC->RemoveActiveGameplayEffect(Handle.Key);
				HandleToRemove.Add(Handle.Key);
			}
		}
		for(auto Handle: HandleToRemove)
		ActiveGameplayEffects.FindAndRemoveChecked(Handle);
	}
}

void AAftermathEffectActor::ApplyEffectOnTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(TargetASC)
	{
	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
		
		FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, EffectLevel, ContextHandle);
		if(SpecHandle != nullptr)
		{
			FActiveGameplayEffectHandle ActiveGameplayEffect = TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			const bool bIsInfinite = SpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
			
			if(bIsInfinite && InfiniteRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
			{
				ActiveGameplayEffects.Add(ActiveGameplayEffect, TargetASC);
			}
		}
	}
}

void AAftermathEffectActor::RemoveEffectOnTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(ASC)
	{
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, EffectLevel, ContextHandle);
		if(SpecHandle != nullptr)
		{
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
	
}

// void AAftermathEffectActor::BeginPlay()
// {
// 	Super::BeginPlay();
// 	ActorSphere->OnComponentBeginOverlap.AddDynamic(this,&AAftermathEffectActor::OnBeginOverlap);
// 	ActorSphere->OnComponentEndOverlap.AddDynamic(this,&AAftermathEffectActor::OnEndOverlap);
// }
