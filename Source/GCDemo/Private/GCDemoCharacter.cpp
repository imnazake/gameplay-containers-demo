// Copyright Epic Games, Inc. All Rights Reserved.

#include "GCDemoCharacter.h"

#include "AbilitySystemComponent.h"
#include "GCDemoPlayerController.h"
#include "GCDemoPlayerState.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/Equipment/EquipmentComponent.h"
#include "Core/Hotbar/HotbarComponent.h"
#include "Core/Inventory/InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AGCDemoCharacter::AGCDemoCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
}

void AGCDemoCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AGCDemoCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AGCDemoPlayerState* PS = GetPlayerState<AGCDemoPlayerState>())
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	
		if (AGCDemoPlayerController* PC = Cast<AGCDemoPlayerController>(PS->GetPlayerController()))
		{
			if (UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
			{
				PC->GetInventoryComponent()->RegisterWithAbilitySystem(ASC);
				PC->GetHotbarComponent()->RegisterWithAbilitySystem(ASC);
				PC->GetEquipmentComponent()->RegisterWithAbilitySystem(ASC);
			}
		}
	}
}

void AGCDemoCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AGCDemoPlayerState* PS = GetPlayerState<AGCDemoPlayerState>())
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();

		if (const AGCDemoPlayerController* PC = Cast<AGCDemoPlayerController>(PS->GetPlayerController()))
		{
			if (ASC)
			{
				PC->GetInventoryComponent()->RegisterWithAbilitySystem(ASC);
				PC->GetHotbarComponent()->RegisterWithAbilitySystem(ASC);
				PC->GetEquipmentComponent()->RegisterWithAbilitySystem(ASC);
			}
		}
	}
}
