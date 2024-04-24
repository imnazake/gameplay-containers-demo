// Copyright (C) 2024 Nazake. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GCDemoEditorTarget : TargetRules
{
	public GCDemoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("GCDemo");
	}
}
