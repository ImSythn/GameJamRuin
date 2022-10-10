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
