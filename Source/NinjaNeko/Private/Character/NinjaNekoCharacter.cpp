// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/NinjaNekoCharacter.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player/NinjaNekoPlayerState.h"

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

void ANinjaNekoCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void ANinjaNekoCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void ANinjaNekoCharacter::InitAbilityActorInfo()
{
	ANinjaNekoPlayerState* NinjaNekoPlayerState = GetPlayerState<ANinjaNekoPlayerState>();
	check(NinjaNekoPlayerState);
	NinjaNekoPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(NinjaNekoPlayerState,this);
	AbilitySystemComponent = NinjaNekoPlayerState->GetAbilitySystemComponent();
	AttributeSet = NinjaNekoPlayerState->GetAttributeSet();
}

