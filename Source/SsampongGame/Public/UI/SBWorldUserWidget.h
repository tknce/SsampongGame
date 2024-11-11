// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBWorldUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class SSAMPONGGAME_API USBWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	// �̵��� �� �ִ� ����
	// ȭ�� ���� ������ ����
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldOffset;

	// ExposeOnSpawn=true ������ ����� ������ ȣ���ϰ�

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (ExposeOnSpawn = true))
	TObjectPtr<AActor> AttachedActor;
};
