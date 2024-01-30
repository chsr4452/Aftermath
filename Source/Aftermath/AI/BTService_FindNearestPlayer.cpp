// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindNearestPlayer.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Player"), FoundActors);

	for(AActor* ActorWithTag:FoundActors)
	{
		GEngine->AddOnScreenDebugMessage(3, .5f, FColor::Green, ActorWithTag->GetName());
	}
}
