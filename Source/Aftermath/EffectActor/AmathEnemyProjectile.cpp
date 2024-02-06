// Fill out your copyright notice in the Description page of Project Settings.


#include "AmathEnemyProjectile.h"


// Sets default values
AAmathEnemyProjectile::AAmathEnemyProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAmathEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmathEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

