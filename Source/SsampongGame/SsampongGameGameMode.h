// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SsampongGameGameMode.generated.h"

UCLASS(minimalapi)
class ASsampongGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// ���� �α���
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// ���ſ� �°� �������̵�
	virtual void ResetLevel() override;

	// GameOver�� ȣ��Ǿ����� Ȯ���ϴ� �Լ�
	virtual bool HasMatchEnded() const override;

	// ���� - �߰��� ����
	// Store�ǹ� �ı�
	UFUNCTION(BlueprintCallable, Category = Game)
	virtual void GameOver();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "DoRestart", ScriptName = "DoRestart"))
	void K2_DoRestart();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "OnGameOver", ScriptName = "OnGameOver"))
	void K2_OnGameOver();

	UPROPERTY(BlueprintReadOnly, Category = Game)
	uint32 bGameOver : 1;

public:
	ASsampongGameGameMode();
};



