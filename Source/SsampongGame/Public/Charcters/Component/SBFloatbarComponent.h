// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBFloatbarComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SSAMPONGGAME_API USBFloatbarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USBFloatbarComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GASDocumentation|UI")
	TSubclassOf<class USBelicaFloatingStatusBarWidget> UIFloatingStatusBarClass;

	UPROPERTY()
	class USBelicaFloatingStatusBarWidget* UIFloatingStatusBar;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GASDocumentation|UI")
	class UWidgetComponent* UIFloatingStatusBarComponent;

	class USBelicaFloatingStatusBarWidget* GetFloatingStatusBar();

	void InitializeFloatingStatusBar();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
