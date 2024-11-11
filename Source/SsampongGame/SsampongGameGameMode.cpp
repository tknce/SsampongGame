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
			// ���� Ŭ���̾�Ʈ�� ������ �� �ִ� ���� ��� ������ ���� �ֵ��� ����
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
