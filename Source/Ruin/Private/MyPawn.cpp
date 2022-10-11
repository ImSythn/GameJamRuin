// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "MyPawn.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup component hierarchy
	PlayerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCapsule"));
	RootComponent = PlayerCapsule;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(PlayerCapsule);
	PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayerSprite"));
	PlayerSprite->SetupAttachment(PlayerCapsule);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePawnByForce();
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AMyPawn::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMyPawn::MoveLR);
}

void AMyPawn::MovePawnByForce()
{
	// Early out if no input is provided
	if (forceFB == FVector::Zero() && forceLR == FVector::Zero())
		return;

	// Combine forceFB and forceLR to create the final force vector and multiply it with MoveForceMultiplier
	FVector force = FVector(forceFB + forceLR).GetSafeNormal() * MoveForceMultiplier;

	UE_LOG(LogTemp, Warning, TEXT("vector values: %s"), *force.ToString());
	// Add force to the PlayerCapsule
	PlayerCapsule->AddForce(force);
}

void AMyPawn::MoveFB(float Value)
{
	forceFB = FVector::ForwardVector * Value;
}

void AMyPawn::MoveLR(float Value)
{
	forceLR = FVector::LeftVector * Value;
}
