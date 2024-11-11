// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBStoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API USBStoreWidget : public UUserWidget
{
	GENERATED_BODY()
public:


	// 버튼 바인딩
	UPROPERTY(meta = (BindWidget))
	class UButton* MetaorButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DashButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SprintButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AttackButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AimDownsightButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PassiveArmorButton;

	UPROPERTY(meta = (BindWidget))
	UButton* HP;

	UPROPERTY(meta = (BindWidget))
	UButton* MP;

	// 각 버튼에 대응되는 함수
	UFUNCTION()
	void OnMetaorButtonPressed();

	UFUNCTION()
	void OnDashButtonPressed();

	UFUNCTION()
	void OnSprintButtonPressed();

	UFUNCTION()
	void OnAttackButtonPressed();

	UFUNCTION()
	void OnAimDownsightButtonPressed();

	UFUNCTION()
	void OnPassiveArmorButtonPressed();

	UFUNCTION()
	void OnAddHP();

	UFUNCTION()
	void OnAddMP();

protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
};
