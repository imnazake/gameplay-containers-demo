/**
 * Copyright (C) 2024 Nazake. All Rights Reserved.
 */

using UnrealBuildTool;

public class GCDemo : ModuleRules
{
	public GCDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core", 
	        "CoreUObject", 
	        "Engine", 
	        "InputCore", 
	        "HeadMountedDisplay", 
	        "NavigationSystem", 
	        "AIModule", 
	        "Niagara", 
	        "EnhancedInput", 
	        "GameplayContainers",
	        "GameplayAbilities",
	        "GameplayTags",
	        "GameplayTasks",
        });
    }
}
