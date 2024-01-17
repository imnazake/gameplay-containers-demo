/**
 * Copyright (C) 2024 Mohamed Labidi (Nazake). All Rights Reserved.
 */

#include "GCDemoAssetManager.h"
#include "AbilitySystemGlobals.h"

void UGCDemoAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
