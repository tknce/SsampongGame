// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SBInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USBInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SSAMPONGGAME_API ISBInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void OnActorLoaded();

	// 아이템 얻을 때 텍스트 관리
	// 부모클래스라 하위 클래스에서 구현
	// 버츄얼 왜 안붙였지
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FText GetInteractText(APawn* InstigatorPawn);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
