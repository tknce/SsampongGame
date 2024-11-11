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
	// 서버 로그인
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// 내거에 맞게 오버라이드
	virtual void ResetLevel() override;

	// GameOver가 호출되었는지 확인하는 함수
	virtual bool HasMatchEnded() const override;

	// 조건 - 추가될 예정
	// Store건물 파괴
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



