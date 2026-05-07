// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject_415 : ModuleRules
{
	public MyProject_415(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MyProject_415",
			"MyProject_415/Variant_Horror",
			"MyProject_415/Variant_Horror/UI",
			"MyProject_415/Variant_Shooter",
			"MyProject_415/Variant_Shooter/AI",
			"MyProject_415/Variant_Shooter/UI",
			"MyProject_415/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
