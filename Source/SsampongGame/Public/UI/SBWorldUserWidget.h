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

	// 이동할 수 있는 위젯
	// 화면 값을 가져온 이유
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldOffset;

	// ExposeOnSpawn=true 변수가 노출될 때마다 호출하게

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (ExposeOnSpawn = true))
	TObjectPtr<AActor> AttachedActor;
};
