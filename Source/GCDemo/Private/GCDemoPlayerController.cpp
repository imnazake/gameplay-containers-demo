// Copyright Epic Games, Inc. All Rights Reserved.

#include "GCDemoPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Core/Equipment/EquipmentComponent.h"
#include "Core/Hotbar/HotbarComponent.h"
#include "Core/Inventory/InventoryComponent.h"

AGCDemoPlayerController::AGCDemoPlayerController()
{
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	InventoryComponent->SetIsReplicated(true);

	HotbarComponent = CreateDefaultSubobject<UHotbarComponent>(TEXT("HotbarComponent"));
	HotbarComponent->SetIsReplicated(true);
	
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	EquipmentComponent->SetIsReplicated(true);
	
}

TArray<UGameplayContainerComponent*> AGCDemoPlayerController::GetGameplayContainers()
{
	TArray<UGameplayContainerComponent*> FoundContainers;

	FoundContainers.Add(EquipmentComponent);
	FoundContainers.Add(InventoryComponent);
	FoundContainers.Add(HotbarComponent);

	return FoundContainers;
}

UInventoryComponent* AGCDemoPlayerController::GetInventoryComponent() const
{
	return InventoryComponent;
}

UHotbarComponent* AGCDemoPlayerController::GetHotbarComponent() const
{
	return HotbarComponent;
}

UEquipmentComponent* AGCDemoPlayerController::GetEquipmentComponent() const
{
	return EquipmentComponent;
}

void AGCDemoPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AGCDemoPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EquipmentComponent->RegisterWithInventoryComponent(InventoryComponent);
}

void AGCDemoPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void AGCDemoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}