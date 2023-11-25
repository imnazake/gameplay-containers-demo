// Fill out your copyright notice in the Description page of Project Settings.

#include "GCDemoPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GCDemoPlayerController.h"
#include "Core/Equipment/EquipmentComponent.h"
#include "Core/Hotbar/HotbarComponent.h"
#include "Core/Inventory/InventoryComponent.h"

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

	if (const AGCDemoPlayerController* PC = Cast<AGCDemoPlayerController>(GetPlayerController()))
	{
		if (AbilitySystemComponent)
		{
			PC->GetInventoryComponent()->RegisterWithAbilitySystem(AbilitySystemComponent);
			PC->GetHotbarComponent()->RegisterWithAbilitySystem(AbilitySystemComponent);
			PC->GetEquipmentComponent()->RegisterWithAbilitySystem(AbilitySystemComponent);
		}
	}
}

UAbilitySystemComponent* AGCDemoPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
