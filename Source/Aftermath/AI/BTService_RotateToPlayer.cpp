// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RotateToPlayer.h"

#include "Aftermath/Enemy/EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_RotateToPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	TargetObject = MyBlackboard->GetValueAsObject(FName("TargetActorToFollow"));
	AActor* TargetActor = Cast<AActor>(TargetObject);
	
	//
	// AActor* EnemyActor = OwnerComp.GetOwner();
	// AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(EnemyActor);
	//
	// AActor* TargetActor = TargetActorToFollowSelector;
}
