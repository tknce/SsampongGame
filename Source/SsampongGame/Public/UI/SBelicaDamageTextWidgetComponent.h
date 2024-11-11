// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SBelicaDamageTextWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API USBelicaDamageTextWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage);
};
