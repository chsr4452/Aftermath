// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Enemy.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class AFTERMATH_API AAIController_Enemy : public AAIController
{
	GENERATED_BODY()

public:
	AAIController_Enemy();

protected:

	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
