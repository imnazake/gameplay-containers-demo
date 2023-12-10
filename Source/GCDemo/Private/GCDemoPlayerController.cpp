// Copyright Epic Games, Inc. All Rights Reserved.

#include "GCDemoPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

AGCDemoPlayerController::AGCDemoPlayerController()
{
}

void AGCDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AGCDemoPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AGCDemoPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void AGCDemoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}