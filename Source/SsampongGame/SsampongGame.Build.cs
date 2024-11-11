// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SsampongGame : ModuleRules
{
	public SsampongGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks", "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
								"Slate", "SlateCore", "AIModule" });
	}
}
