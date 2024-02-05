// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindNearestPlayer.h"
#include <cfloat>
#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Player"), FoundActors);

	AActor * NearestActor = nullptr;
	float NearestDistance = FLT_MAX;
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	for(AActor* ActorWithTag:FoundActors)
	{
		// GEngine->AddOnScreenDebugMessage(3, .5f, FColor::Green, ActorWithTag->GetName());
		if(IsValid(OwnerPawn) && IsValid(ActorWithTag))
		{
			if(NearestDistance >  OwnerPawn->GetDistanceTo(ActorWithTag))
			{
				NearestDistance =  OwnerPawn->GetDistanceTo(ActorWithTag);
				NearestActor = ActorWithTag;
			}
		}
	}
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, TargetActorDistanceSelector, NearestDistance);
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetActorToFollowSelector, NearestActor);
}
