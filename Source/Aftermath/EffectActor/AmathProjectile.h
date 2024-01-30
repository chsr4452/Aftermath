// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"

#include "AmathProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
UCLASS()
class AFTERMATH_API AAmathProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmathProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadOnly, meta = (ExpostOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
	UPROPERTY(BlueprintReadOnly, meta = (ExpostOnSpawn = true))
	FGameplayEffectSpecHandle EffectBurnSpecHandle;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
private:

	float LifeSpan = 5.f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopSound;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> LoopSoundComponent;
};
