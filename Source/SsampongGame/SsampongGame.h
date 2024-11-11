// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/StructuredLog.h"

UENUM(BlueprintType)
enum class DemoAbilityID : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel"),
	Dash UMETA(DisplayName = "Dash"),
	Metaor UMETA(DisplayName = "Metaor"),
	Attack UMETA(DisplayName = "Attack"),
	EnemyAttack UMETA(DisplayName = "EnemyAttack"),
	AimDownsight UMETA(DisplayName = "AimDownsight"),
	PassiveArmor  UMETA(DisplayName = "PassiveArmor"),
	Sprint UMETA(DisplayName = "Sprint"),
};



// Define new "stat command" group shown in-game via "stat stanford"
DECLARE_STATS_GROUP(TEXT("STANFORD_Game"), STATGROUP_STANFORD, STATCAT_Advanced);

// Define category "LogGame"
SSAMPONGGAME_API DECLARE_LOG_CATEGORY_EXTERN(LogGame, Log, All);

// Define alias to easily keep track of custom channels in C++ (must match what is specified in Project Settings > Collision 
#define COLLISION_PROJECTILE ECC_GameTraceChannel1


static void LogOnScreen(UObject* WorldContext, FString Msg, FColor Color = FColor::White, float Duration = 5.0f)
{
	if (!ensure(WorldContext))
	{
		return;
	}

	UWorld* World = WorldContext->GetWorld();
	if (!ensure(World))
	{
		return;
	}


	FString NetPrefix = World->IsNetMode(NM_Client) ? "[CLIENT] " : "[SERVER] ";
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, NetPrefix + Msg);
	}
}