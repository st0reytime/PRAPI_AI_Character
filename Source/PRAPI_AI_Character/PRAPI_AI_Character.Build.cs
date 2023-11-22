// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PRAPI_AI_Character : ModuleRules
{
	public PRAPI_AI_Character(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "EnhancedInput", "GameplayTasks" });
	}
}
