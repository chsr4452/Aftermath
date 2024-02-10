// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_RotateToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AFTERMATH_API UBTService_RotateToPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()
protected:
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
    	FBlackboardKeySelector MyBlackboardKeySelector;

		UObject* TargetObject;
private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

};
