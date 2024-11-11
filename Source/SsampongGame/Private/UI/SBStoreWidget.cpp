// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBStoreWidget.h"

#include "SBelicaCharacter.h"
#include "Charcters/SBelicaPlayerCharacter.h"
#include "Components/Button.h"

void USBStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Metaor ��ư Ŭ�� �̺�Ʈ�� �Լ��� ���ε�
	if (MetaorButton)
	{
		MetaorButton->OnClicked.AddDynamic(this, &USBStoreWidget::OnMetaorButtonPressed);
	}

	// Dash ��ư Ŭ�� �̺�Ʈ�� �Լ��� ���ε�
	if (DashButton)
	{
		DashButton->OnClicked.AddDynamic(this, &USBStoreWidget::OnDashButtonPressed);
	}

	// Sprint ��ư Ŭ�� �̺�Ʈ�� �Լ��� ���ε�
	if (SprintButton)
	{
		SprintButton->OnClicked.AddDynamic(this, &USBStoreWidget::OnSprintButtonPressed);
	}

	// Attack ��ư Ŭ�� �̺�Ʈ�� �Լ��� ���ε�
	if (AttackButton)
	{
		AttackButton->OnClicked.AddDynamic(this, &USBStoreWidget::OnAttackButtonPressed);
	}

	// AimDownsight ��ư Ŭ�� �̺�Ʈ�� �Լ��� ���ε�
	if (AimDownsightButton)
	{
		AimDownsightButton->OnClicked.AddDynamic(this, &USBStoreWidget::OnAimDownsightButtonPressed);
	}

	// PassiveArmor ��ư Ŭ�� �̺�Ʈ�� �Լ��� ���ε�
	if (PassiveArmorButton)
	{
		PassiveArmorButton->OnClicked.AddDynamic(this, &USBStoreWidget::OnPassiveArmorButtonPressed);
	}

	if (HP)
	{
		HP->OnClicked.AddDynamic(this, &USBStoreWidget::OnAddHP);
	}

	if (MP)
	{
		MP->OnClicked.AddDynamic(this, &USBStoreWidget::OnAddMP);
	}

	// SetKeyboardFocus();
}

void USBStoreWidget::OnMetaorButtonPressed()
{
	ASBelicaCharacter* BelicaCharacter = Cast<ASBelicaCharacter>(GetOwningPlayerPawn());
	if (BelicaCharacter)
	{
		BelicaCharacter->InputButtonAddAbility(DemoAbilityID::Metaor);
	}
}

void USBStoreWidget::OnDashButtonPressed()
{
	ASBelicaCharacter* BelicaCharacter = Cast<ASBelicaCharacter>(GetOwningPlayerPawn());
	if (BelicaCharacter)
	{
		BelicaCharacter->InputButtonAddAbility(DemoAbilityID::Dash);
	}
}

void USBStoreWidget::OnSprintButtonPressed()
{
	ASBelicaCharacter* BelicaCharacter = Cast<ASBelicaCharacter>(GetOwningPlayerPawn());
	if (BelicaCharacter)
	{
		BelicaCharacter->InputButtonAddAbility(DemoAbilityID::Sprint);
	}
}

void USBStoreWidget::OnAttackButtonPressed()
{
	ASBelicaCharacter* BelicaCharacter = Cast<ASBelicaCharacter>(GetOwningPlayerPawn());
	if (BelicaCharacter)
	{
		BelicaCharacter->InputButtonAddAbility(DemoAbilityID::Attack);
	}
}

void USBStoreWidget::OnAimDownsightButtonPressed()
{
	ASBelicaCharacter* BelicaCharacter = Cast<ASBelicaCharacter>(GetOwningPlayerPawn());
	if (BelicaCharacter)
	{
		BelicaCharacter->InputButtonAddAbility(DemoAbilityID::AimDownsight);
	}
}

void USBStoreWidget::OnPassiveArmorButtonPressed()
{
	ASBelicaCharacter* BelicaCharacter = Cast<ASBelicaCharacter>(GetOwningPlayerPawn());
	if (BelicaCharacter)
	{
		BelicaCharacter->InputButtonAddAbility(DemoAbilityID::PassiveArmor);
	}
}

void USBStoreWidget::OnAddHP()
{
	ASBelicaCharacter* BelicaCharacter = Cast<ASBelicaCharacter>(GetOwningPlayerPawn());

	if (BelicaCharacter)
	{
		BelicaCharacter->SetMaxHealth(10);
	}
}

void USBStoreWidget::OnAddMP()
{
	ASBelicaCharacter* BelicaCharacter = Cast<ASBelicaCharacter>(GetOwningPlayerPawn());

	if (BelicaCharacter)
	{
		BelicaCharacter->SetMaxMana(10);
	}
}

FReply USBStoreWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// F Ű �Է� ó��
	if (InKeyEvent.GetKey() == EKeys::F)
	{
		// UI �ݱ� ��û
		if (ASBelicaPlayerCharacter* Character = Cast<ASBelicaPlayerCharacter>(GetOwningPlayerPawn()))
		{
			Character->Interact_OnlyUI();
		}
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void USBStoreWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}
