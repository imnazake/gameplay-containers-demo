// Copyright (C) 2024 Nazake. All Rights Reserved.

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
#include "GameFramework/PlayerController.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGCDemoCharacter::AGCDemoCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 90.0f);
	
	GetMesh()->SetupAttachment(GetCapsuleComponent());

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 500.0f;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom);
	ThirdPersonCamera->bUsePawnControlRotation = false;
	
	UpperBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperBodyMesh"));
	UpperBodyMesh->SetupAttachment(GetMesh());
	
	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMesh"));
	HandsMesh->SetupAttachment(GetMesh());

	LowerBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBodyMesh"));
	LowerBodyMesh->SetupAttachment(GetMesh());

	// This shit right here was causing player to shake when moving backwards, took me a long time to figure it out !!!
	GetCharacterMovement()->bOrientRotationToMovement = false;
	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 750.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
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

void AGCDemoCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (const TScriptInterface<IGameplayContainerInterface> Interface = GetController())
	{
		EquipmentComponent->RegisterWithInventoryComponent(Interface->GetInventoryComponent());
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
				GetEquipmentComponent()->RegisterWithAbilitySystem(ASC);
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

		if (const AGCDemoPlayerController* PC = Cast<AGCDemoPlayerController>(PS->GetPlayerController()))
		{
			if (UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
			{
				PC->GetInventoryComponent()->RegisterWithAbilitySystem(ASC);
				PC->GetHotbarComponent()->RegisterWithAbilitySystem(ASC);
				GetEquipmentComponent()->RegisterWithAbilitySystem(ASC);
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
