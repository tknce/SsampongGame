// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "SsampongGame/SsampongGame.h"

void USBWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// ai가 죽을 경우 삭제
	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();

		//UE_LOGFMT(LogGame, Warning, "AttachedActor no longer valid, removing Health Widget.");
		return;
	}

	// 월드스크린에 호출
	FVector2D ScreenPosition;
	bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition);

	if (bIsOnScreen)
	{
		// 뷰포트 가져오기
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		// 실제 포지션이랑 동기화
		ScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			// 구한 위치에 랜더링
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}

	if (ParentSizeBox)
	{
		ParentSizeBox->SetVisibility(bIsOnScreen ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}
