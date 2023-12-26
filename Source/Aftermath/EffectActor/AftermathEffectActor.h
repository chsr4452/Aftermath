// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AftermathEffectActor.generated.h"

class USphereComponent;

UCLASS()
class AFTERMATH_API AAftermathEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAftermathEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "EffectActor")
	TObjectPtr<USphereComponent> ActorSphere;

	UPROPERTY(EditAnywhere, Category = "EffectActor")
	TObjectPtr<UStaticMeshComponent> ActorMesh;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor*  OtherActor, UPrimitiveComponent*  OtherComp, int32  OtherBodyIndex, bool  bFromSweep, const FHitResult &  SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
