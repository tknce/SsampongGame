// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SBWeaponBase.h"

// Sets default values
ASBWeaponBase::ASBWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASBWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

