// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SBelicaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API ASBelicaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void CreateHUD();

	class USHUDWidget* GetHUD();
protected:


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GASDocumentation|UI")
	TSubclassOf<class USHUDWidget> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "GASDocumentation|UI")
	class USHUDWidget* UIHUDWidget;

	// ¼­¹ö¸¸
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;
};
