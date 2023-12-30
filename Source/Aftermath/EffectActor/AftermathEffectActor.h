// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AftermathEffectActor.generated.h"

class UAbilitySystemComponent;

class UGameplayEffect;
class USphereComponent;

UENUM()
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM()
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AFTERMATH_API AAftermathEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAftermathEffectActor();

protected:
	// Called when the game starts or when spawned
	// virtual void BeginPlay() override;

	//Instant
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay|Effect")
	TSubclassOf<UGameplayEffect> InstantEffectClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay|Effect")
	EEffectApplicationPolicy InstantApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	//Duration
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay|Effect")
	TSubclassOf<UGameplayEffect> DurationEffectClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay|Effect")
	EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	//Infinite
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay|Effect")
	TSubclassOf<UGameplayEffect> InfiniteEffectClass;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay|Effect")
	EEffectApplicationPolicy InfiniteApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay|Effect")
	EEffectRemovalPolicy InfiniteRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
private:
	// UPROPERTY(EditAnywhere, Category = "EffectActor")
	// TObjectPtr<USphereComponent> ActorSphere;

	UPROPERTY(EditAnywhere, Category = "EffectActor")
	TObjectPtr<UStaticMeshComponent> ActorMesh;

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);
	//
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectOnTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void RemoveEffectOnTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveGameplayEffects;
};
