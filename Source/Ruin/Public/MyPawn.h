// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class RUIN_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/*
	 * Look
	 */
	// The multiplier to apply to the look sensitivity
	UPROPERTY(Category="Look", EditAnywhere, NoClear)
	float HorizontalSensitivity = 1.0f;
	UPROPERTY(Category="Look", EditAnywhere, NoClear)
	float VerticalSensitivity = 1.0f;

	// Current rotator used for forward movement and keeping the camera oriented with pawn orientation. 
	FRotator CurrentRotator;
	
	/*
	 * Move
	 */
	// The multiplier to apply to the movement force
	UPROPERTY(Category="Move", EditAnywhere, NoClear)
	float MoveForceMultiplier = 100000.0f;

	// Input force
	float InputForceFB;
	float InputForceLR;

	// Normalizes
	FVector GetInputVector();
	// Move function
	void MovePawnByForce();
	// Generate movement vectors for left and right movement
	void MoveFB(float Value);
	void MoveLR(float Value);
	// rotate around Z axis of capsule to look left and right 
	void LookLR(float Value);
	// rotate around Y axis of camera to look up and down
	void LookUD(float Value);
	
	// Capsule component for collision
	UPROPERTY(EditDefaultsOnly)
	UCapsuleComponent* PlayerCapsule;

	// Sprite
	UPROPERTY(EditDefaultsOnly)
	UPaperSpriteComponent* PlayerSprite;

	// Camera
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;
};
