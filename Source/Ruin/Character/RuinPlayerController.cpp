// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "Ruin/Character/RuinPlayerController.h"

#include "RuinCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Ruin/LogCategories.h"

void ARuinPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// If no valid character is possessed, don't bind input components.
	if (!PossessedRuinCharacter)
		return;
	
	InputComponent->BindAxis("MoveForward", this, &ARuinPlayerController::MoveForwardCallback);
	InputComponent->BindAxis("MoveRight", this, &ARuinPlayerController::MoveRightCallback);
	InputComponent->BindAxis("LookUp", this, &ARuinPlayerController::LookUpCallback);
	InputComponent->BindAxis("Turn", this, &ARuinPlayerController::TurnCallback);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ARuinPlayerController::JumpCallback);
	InputComponent->BindAction("Jump", IE_Released, this, &ARuinPlayerController::StopJumpCallback);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &ARuinPlayerController::CrouchCallback);
	InputComponent->BindAction("Crouch", IE_Released, this, &ARuinPlayerController::UnCrouchCallback);
}

void ARuinPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// Check if possessed pawn is of type ARuinCharacter, if not UnPossess this pawn
	if (ARuinCharacter* DerivedPawn = dynamic_cast<ARuinCharacter*>(InPawn))
	{
		PossessedRuinCharacter = DerivedPawn;
		SetupInputComponent();
	}
	else
	{
		UE_LOG(LogCharacter, Warning, TEXT("Cannot possess character of type: \"APawn\""));
		UnPossess();
	}
}

void ARuinPlayerController::MoveForwardCallback(float AxisValue)
{
	//if (PossessedRuinCharacter)
	PossessedRuinCharacter->AddMovementInput(PossessedRuinCharacter->GetActorForwardVector(), AxisValue);
}

void ARuinPlayerController::MoveRightCallback(float AxisValue)
{
	//if (PossessedRuinCharacter)
	PossessedRuinCharacter->AddMovementInput(PossessedRuinCharacter->GetActorRightVector(), AxisValue);
}

void ARuinPlayerController::LookUpCallback(float AxisValue)
{
	//if (PossessedRuinCharacter)
	PossessedRuinCharacter->AddControllerPitchInput(AxisValue);
}

void ARuinPlayerController::TurnCallback(float AxisValue)
{
	//if (PossessedRuinCharacter)
	PossessedRuinCharacter->AddControllerYawInput(AxisValue);
}

void ARuinPlayerController::JumpCallback()
{
	//if (PossessedRuinCharacter)
	PossessedRuinCharacter->Jump();
}

void ARuinPlayerController::StopJumpCallback()
{
	//if (PossessedRuinCharacter)
	PossessedRuinCharacter->StopJumping();
}

void ARuinPlayerController::CrouchCallback()
{
	//if (PossessedRuinCharacter)
	PossessedRuinCharacter->Crouch();
}

void ARuinPlayerController::UnCrouchCallback()
{
	//if (PossessedRuinCharacter)
	PossessedRuinCharacter->UnCrouch();
}
