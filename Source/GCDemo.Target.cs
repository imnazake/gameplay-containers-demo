// Copyright (C) 2024 Nazake. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GCDemoTarget : TargetRules
{
	public GCDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("GCDemo");
	}
}
