/**
 * Copyright (C) 2024 Nazake. All Rights Reserved.
 */

#include "GCDemoPlayerState.h"
#include "AbilitySystemComponent.h"

AGCDemoPlayerState::AGCDemoPlayerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AbilitySystemComponent->SetIsReplicated(true);

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
}

UAbilitySystemComponent* AGCDemoPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
