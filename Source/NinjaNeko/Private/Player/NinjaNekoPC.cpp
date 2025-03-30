// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NinjaNekoPC.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"

ANinjaNekoPC::ANinjaNekoPC()
{
	bReplicates = true;
}

void ANinjaNekoPC::BeginPlay()
{
	Super::BeginPlay();
	check(NinjaNekoContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(NinjaNekoContext, 0);

	bShowMouseCursor = false;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ANinjaNekoPC::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Jumping
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ANinjaNekoPC::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ANinjaNekoPC::StopJumping);

	// Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANinjaNekoPC::Move);
}

void ANinjaNekoPC::Move(const FInputActionValue& Value)
{
	// input is a float
	float MovementDirection = Value.Get<float>();
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// Move right or left
		ControlledPawn->AddMovementInput(FVector(1.f, 0.f, 0.f), MovementDirection);

		// Flip character to face movement direction
		if (MovementDirection > 0)
		{
			// Smoothly rotate to face right
			FRotator TargetRotation = FRotator(0.f, 0.f, 0.f);
			ControlledPawn->SetActorRotation(FMath::RInterpTo(ControlledPawn->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f));
		}
		else if (MovementDirection < 0)
		{
			// Smoothly rotate to face left
			FRotator TargetRotation = FRotator(0.f, 180.f, 0.f);
			ControlledPawn->SetActorRotation(FMath::RInterpTo(ControlledPawn->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f));
		}
	}
}

void ANinjaNekoPC::Jump(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn) )
		{
			ControlledCharacter->Jump();
		}
	}
}

void ANinjaNekoPC::StopJumping(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn) )
		{
			ControlledCharacter->StopJumping();
		}
	}
}
