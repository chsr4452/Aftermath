// Fill out your copyright notice in the Description page of Project Settings.


#include "AftermathEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "EditorDirectories.h"
#include "Aftermath/GameplayAbility/AftermathAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAftermathEffectActor::AAftermathEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>("ActorMesh");
	SetRootComponent(ActorMesh);
	
	ActorSphere = CreateDefaultSubobject<USphereComponent>("ActorSphere");
	ActorSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
//
// void AAftermathEffectActor::OnBeginOverlap(
// 	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
// 	bool bFromSweep, const FHitResult& SweepResult)
// {
// 		IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
// 	
// 		const UAftermathAttributeSet* AftermathAttributeSet =  Cast<UAftermathAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAftermathAttributeSet::StaticClass()));
// 		UAftermathAttributeSet * MutableAftermathAttributeSet = const_cast<UAftermathAttributeSet*>(AftermathAttributeSet);
// 		MutableAftermathAttributeSet->SetHealth(AftermathAttributeSet->GetHealth() + 25.f);
// 		MutableAftermathAttributeSet->SetMana(AftermathAttributeSet->GetMana() + 5.f);
// 		Destroy();
// 	
// }
//
// void AAftermathEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// }

void AAftermathEffectActor::ApplyEffectOnTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(ASC)
	{
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
		
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, ELastDirectory::LEVEL, ContextHandle);
		if(SpecHandle != nullptr)
		{
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

// void AAftermathEffectActor::BeginPlay()
// {
// 	Super::BeginPlay();
// 	ActorSphere->OnComponentBeginOverlap.AddDynamic(this,&AAftermathEffectActor::OnBeginOverlap);
// 	ActorSphere->OnComponentEndOverlap.AddDynamic(this,&AAftermathEffectActor::OnEndOverlap);
// }
