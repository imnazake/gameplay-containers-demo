/**
 * Copyright (C) 2024 Nazake. All Rights Reserved.
 */

using UnrealBuildTool;
using System.Collections.Generic;

public class GCDemoEditorTarget : TargetRules
{
	public GCDemoEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("GCDemo");
	}
}
