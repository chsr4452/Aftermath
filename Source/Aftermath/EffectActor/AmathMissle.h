// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmathMissle.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class AFTERMATH_API AAmathMissle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAmathMissle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY()
	TObjectPtr<USceneComponent> Scene;
	
	UPROPERTY(EDitAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
};
