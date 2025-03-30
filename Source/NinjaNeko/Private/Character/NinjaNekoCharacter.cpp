// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/NinjaNekoCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ANinjaNekoCharacter::ANinjaNekoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Disable movement-based rotation
	bUseControllerRotationYaw = false; // Disable movement-based rotation
	// GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	// Configure Character Movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Constrain character to 2D movement
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f)); // Locks movement to X-Z plane
	
	// Create a Camera Boom (Spring Arm)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;  // Camera distance
	CameraBoom->bUsePawnControlRotation = false;  // Don't rotate camera with character
	CameraBoom->bInheritYaw = false;
	CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));  // Side view

	// Create a Side View Camera
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named NinjaNekoCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
							// Input //
//////////////////////////////////////////////////////////////////////////

void ANinjaNekoCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ANinjaNekoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANinjaNekoCharacter::Move);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANinjaNekoCharacter::Move(const FInputActionValue& Value)
{
	// input is a float
	float MovementDirection = Value.Get<float>();

	if (Controller != nullptr)
	{
		// Move right or left
		AddMovementInput(FVector(1.f, 0.f, 0.f), MovementDirection);

		// Flip character to face movement direction
		if (MovementDirection > 0)
		{
			// Smoothly rotate to face right
			FRotator TargetRotation = FRotator(0.f, 0.f, 0.f);
			SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f));
		}
		else if (MovementDirection < 0)
		{
			// Smoothly rotate to face left
			FRotator TargetRotation = FRotator(0.f, 180.f, 0.f);
			SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f));
		}
	}
}

