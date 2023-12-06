// Copyright Epic Games, Inc. All Rights Reserved.

#include "GCDemoCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
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

	// // Don't rotate character to camera direction
	// bUseControllerRotationPitch = false;
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;

	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(GetMesh());
	HeadMesh->bOwnerNoSee = true;

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh"));
	HandsMesh->SetupAttachment(GetMesh());

	LowerBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBodyMesh"));
	LowerBodyMesh->SetupAttachment(GetMesh());
	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(HeadMesh);
	FirstPersonCamera->bUsePawnControlRotation = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
}

void AGCDemoCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
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

void AGCDemoCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGCDemoCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGCDemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
}
