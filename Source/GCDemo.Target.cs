/**
 * Copyright (C) 2024 Mohamed Labidi (Nazake). All Rights Reserved.
 */

using UnrealBuildTool;
using System.Collections.Generic;

public class GCDemoTarget : TargetRules
{
	public GCDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("GCDemo");
	}
}
