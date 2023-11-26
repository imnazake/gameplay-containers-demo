// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GCDemoPlayerState.generated.h"

class UAbilitySystemComponent;

UCLASS()
class GCDEMO_API AGCDemoPlayerState : public APlayerState, public IAbilitySystemInterface 
{
	GENERATED_BODY()

public:

	AGCDemoPlayerState();
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	
	
	//~ IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ IAbilitySystemInterface


protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	
};
