// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Store/SBBasicStore.h"
#include "Charcters/SBInterface.h"
#include "SBMainStore.generated.h"

class USBFloatbarComponent;
/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API ASBMainStore : public ASBBasicStore, public ISBInterface
{
	GENERATED_BODY()
public:
	ASBMainStore();

	virtual void BeginPlay() override;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual void OnActorLoaded_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class USBStoreWidget> UIStoreClass;

	UPROPERTY()
	USBStoreWidget* UIStore;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GASDocumentation|UI")
	class UWidgetComponent* UIStoreComponent;

	USBFloatbarComponent* FloatbarComponent;

	void HealthChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ToggleUI();
};
