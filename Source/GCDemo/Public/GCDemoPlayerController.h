/**
 * Copyright (C) 2024 Mohamed Labidi (Nazake). All Rights Reserved.
 */

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Core/TestPlayerController.h"
#include "GCDemoPlayerController.generated.h"

UCLASS()
class AGCDemoPlayerController : public ATestPlayerController
{
	GENERATED_BODY()

public:
	
	AGCDemoPlayerController();

protected:

	virtual void PostInitializeComponents() override;
	virtual void OnRep_PlayerState() override;

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
};


