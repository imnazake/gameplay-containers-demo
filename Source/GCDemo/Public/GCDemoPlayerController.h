// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Core/IGameplayContainerInterface.h"
#include "GCDemoPlayerController.generated.h"

class UEquipmentComponent;
class UHotbarComponent;
class UInventoryComponent;
/** Forward declaration to improve compiling times */
class UNiagaraSystem;

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

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TArray<class UInputMappingContext*> InputMappingContexts;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetDestinationTouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Containers)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Containers)
	UHotbarComponent* HotbarComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Containers)
	UEquipmentComponent* EquipmentComponent;

protected:

	virtual void PostInitializeComponents() override;
	virtual void OnRep_PlayerState() override;
	
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};


