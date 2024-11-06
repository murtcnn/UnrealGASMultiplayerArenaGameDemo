// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GASMultiplayerArena : ModuleRules
{
	public GASMultiplayerArena(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
