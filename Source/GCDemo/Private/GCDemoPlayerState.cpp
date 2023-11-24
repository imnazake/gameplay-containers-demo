// Fill out your copyright notice in the Description page of Project Settings.

#include "GCDemoPlayerState.h"
#include "AbilitySystemComponent.h"

AGCDemoPlayerState::AGCDemoPlayerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
}

UAbilitySystemComponent* AGCDemoPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
