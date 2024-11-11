// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "SsampongGame/SsampongGame.h"

void USBWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// ai�� ���� ��� ����
	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();

		//UE_LOGFMT(LogGame, Warning, "AttachedActor no longer valid, removing Health Widget.");
		return;
	}

	// ���彺ũ���� ȣ��
	FVector2D ScreenPosition;
	bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition);

	if (bIsOnScreen)
	{
		// ����Ʈ ��������
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		// ���� �������̶� ����ȭ
		ScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			// ���� ��ġ�� ������
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}

	if (ParentSizeBox)
	{
		ParentSizeBox->SetVisibility(bIsOnScreen ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}
