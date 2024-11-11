// Copyright Epic Games, Inc. All Rights Reserved.

#include "SsampongGameGameMode.h"
#include "SsampongGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/GameStateBase.h"
#include <SBelicaPlayerController.h>


ASsampongGameGameMode::ASsampongGameGameMode()
{
	GameStateClass = ASsampongGameGameMode::StaticClass();
	PlayerControllerClass = ASBelicaPlayerController::StaticClass();
	bGameOver = false;
}

void ASsampongGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	int32 NPlayer = GameState.Get()->PlayerArray.Num();
	if (NPlayer == 2)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			bUseSeamlessTravel = true;
			// 맵이 클라이언트가 연결할 수 있는 수신 대기 서버로 열려 있도록 지정
			World->ServerTravel(FString("/Game/Maps/SsampongMap?listen"));
		}
	}
}

void ASsampongGameGameMode::ResetLevel()
{
	K2_DoRestart();
}

bool ASsampongGameGameMode::HasMatchEnded() const
{
	return bGameOver;
}

void ASsampongGameGameMode::GameOver()
{
	if (bGameOver == false)
	{
		K2_OnGameOver();
		bGameOver = true;
	}
}
