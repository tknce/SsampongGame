// Fill out your copyright notice in the Description page of Project Settings.


#include "Store/SBBasicStore.h"

#include "AbilitySystemComponent.h"
#include "BasicAttributeSet.h"
#include "Charcters/Abilities/SAbilitySystemComponent.h"

// Sets default values
ASBBasicStore::ASBBasicStore()
{
	// Create ability system component, and set it to be explicitly replicated
	HardRefAbilitySystemComponent = CreateDefaultSubobject<USAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	HardRefAbilitySystemComponent->SetIsReplicated(true);

	// Minimal Mode means that no GameplayEffects will replicate. They will only live on the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	HardRefAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	// Set our parent's TWeakObjectPtr
	AbilitySystemComponent = HardRefAbilitySystemComponent;

	HardRefAttributeSetBase = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("AttributeSetBase"));

	BasicAttributeSet = HardRefAttributeSetBase;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}


// Called when the game starts or when spawned
void ASBBasicStore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBBasicStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

