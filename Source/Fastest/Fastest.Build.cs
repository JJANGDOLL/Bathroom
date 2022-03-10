// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Fastest : ModuleRules
{
	public Fastest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PrivateIncludePaths.Add("Fastest");
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

	}
}
