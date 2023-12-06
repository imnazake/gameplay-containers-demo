// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Core/IGameplayContainerInterface.h"
#include "GCDemoPlayerController.generated.h"

class UEquipmentComponent;
class UHotbarComponent;
class UInventoryComponent;

UCLASS()
class AGCDemoPlayerController : public APlayerController, public IGameplayContainerInterface
{
	GENERATED_BODY()

public:
	
	AGCDemoPlayerController();

	virtual TArray<UGameplayContainerComponent*> GetGameplayContainers() override;

	UFUNCTION(BlueprintPure, Category = "Containers")
	UInventoryComponent* GetInventoryComponent() const;

	UFUNCTION(BlueprintPure, Category = "Containers")
	UHotbarComponent* GetHotbarComponent() const;

	UFUNCTION(BlueprintPure, Category = "Containers")
	UEquipmentComponent* GetEquipmentComponent() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Containers)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Containers)
	UHotbarComponent* HotbarComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Containers)
	UEquipmentComponent* EquipmentComponent;

protected:

	virtual void PostInitializeComponents() override;
	virtual void OnRep_PlayerState() override;

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
};


