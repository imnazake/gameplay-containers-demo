/**
 * Copyright (C) 2024 Mohamed Labidi (Nazake). All Rights Reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "GCDemoAssetManager.generated.h"

/**
 * UGCDemoAssetManager
 */
UCLASS()
class GCDEMO_API UGCDemoAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	
	virtual void StartInitialLoading() override;
	
};
