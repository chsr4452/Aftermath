// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AFTERMATH_API UBTService_FindNearestPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector TargetActorToFollowSelector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector TargetActorDistanceSelector;
	
};
