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
	bShowMouseCursor = true;
	
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;

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
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (const UInputMappingContext* IMC: InputMappingContexts)
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
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
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AGCDemoPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AGCDemoPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AGCDemoPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AGCDemoPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AGCDemoPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AGCDemoPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AGCDemoPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AGCDemoPlayerController::OnTouchReleased);
	}
}

void AGCDemoPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AGCDemoPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AGCDemoPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AGCDemoPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AGCDemoPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
