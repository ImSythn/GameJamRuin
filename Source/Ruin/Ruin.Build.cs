// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

using UnrealBuildTool;

public class Ruin : ModuleRules
{
	public Ruin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"UMG", 
			"Paper2D",
			"EditorScriptingUtilities"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"PhysicsCore",
			"OnlineSubsystem",
			"OnlineSubsystemNull",
			"OnlineSubsystemSteam"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
