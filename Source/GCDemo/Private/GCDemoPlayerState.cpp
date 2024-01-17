/**
 * Copyright (C) 2024 Mohamed Labidi (Nazake). All Rights Reserved.
 */

#include "GCDemoPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Core/Equipment/EquipmentComponent.h"
#include "Core/Inventory/InventoryComponent.h"
#include "Core/Hotbar/HotbarComponent.h"
#include "AbilitySystemGlobals.h"
#include "Core/IGameplayContainerInterface.h"

AGCDemoPlayerState::AGCDemoPlayerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// AbilitySystemComponent needs to be updated at a high frequency.
	NetUpdateFrequency = 100.0f;
}

void AGCDemoPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void AGCDemoPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UAbilitySystemGlobals::Get().InitGlobalData();

	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
	
	if (const TScriptInterface<IGameplayContainerInterface> Interface = GetPlayerController())
	{
		if (AbilitySystemComponent)
		{
			Interface->GetInventoryComponent()->RegisterWithAbilitySystem(AbilitySystemComponent);
			Interface->GetHotbarComponent()->RegisterWithAbilitySystem(AbilitySystemComponent);
		}
	}

	if (const TScriptInterface<IGameplayContainerInterface> Interface = GetPawn())
	{
		Interface->GetEquipmentComponent()->RegisterWithAbilitySystem(AbilitySystemComponent);
	}
}

UAbilitySystemComponent* AGCDemoPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
