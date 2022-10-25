// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "Ruin/Core/Character/RuinPlayerController.h"

#include "RuinCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void ARuinPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

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
	
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
}

void ARuinPlayerController::MoveForwardCallback(float AxisValue)
{
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), AxisValue);
}

void ARuinPlayerController::MoveRightCallback(float AxisValue)
{
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), AxisValue);
}

void ARuinPlayerController::LookUpCallback(float AxisValue)
{
	PlayerCharacter->AddControllerPitchInput(AxisValue);
}

void ARuinPlayerController::TurnCallback(float AxisValue)
{
	PlayerCharacter->AddControllerYawInput(AxisValue);
}

void ARuinPlayerController::JumpCallback()
{
	PlayerCharacter->Jump();
}

void ARuinPlayerController::StopJumpCallback()
{
	PlayerCharacter->StopJumping();
}

void ARuinPlayerController::CrouchCallback()
{
	PlayerCharacter->Crouch();
}

void ARuinPlayerController::UnCrouchCallback()
{
	PlayerCharacter->UnCrouch();
}
