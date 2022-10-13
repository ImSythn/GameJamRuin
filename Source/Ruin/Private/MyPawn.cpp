// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "MyPawn.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	PlayerInputComponent->BindAxis(TEXT("LookLR"), this, &AMyPawn::LookLR);
	PlayerInputComponent->BindAxis(TEXT("LookUD"), this, &AMyPawn::LookUD);
}

FVector AMyPawn::GetInputVector()
{
	// Unrefined input vector
	FVector InputVector = FVector(InputForceFB,InputForceLR,0);
	
	// Check if input vector is bigger than a unit vector, if so, normalization is needed
	if (InputVector.Length() > 1.0f)
	{
		// Normalize input vector
		return InputVector.GetSafeNormal();
	}
	
	return InputVector;
}

void AMyPawn::MovePawnByForce()
{
	// Early out if no input is provided
	if (InputForceFB == 0.0f && InputForceLR == 0.0f)
		return;

	// Calculate FB and LR move direction strength.
	FVector InputVector = GetInputVector();
		
	UE_LOG(LogTemp, Warning, TEXT("MoveNormal: %s"), *InputVector.ToString());

	// Combine the look direction and the force
	FVector MoveForceVector = InputVector * MoveForceMultiplier;

	FVector RelativeForceVector = UKismetMathLibrary::TransformDirection(GetActorTransform(), MoveForceVector);
	
	// Add force to the PlayerCapsule
	PlayerCapsule->AddForce(RelativeForceVector);
}

void AMyPawn::MoveFB(float Value)
{
	InputForceFB = Value;
}

void AMyPawn::MoveLR(float Value)
{
	InputForceLR = Value;
}

void AMyPawn::LookLR(float Value)
{
	CurrentRotator = GetActorRotation();
	float RotationToAdd = Value * HorizontalSensitivity;
	FRotator NewRotation = CurrentRotator.Add(0, RotationToAdd, 0);
	SetActorRotation(NewRotation);
}

void AMyPawn::LookUD(float Value)
{
	FRotator CameraRotator = PlayerCamera->GetComponentRotation();
	float RotationToAdd = Value * VerticalSensitivity;
	FRotator NewRotation = CameraRotator.Add(RotationToAdd, 0, 0);

	NewRotation.Yaw = CurrentRotator.Yaw;
	NewRotation.Roll = 0;

	PlayerCamera->SetWorldRotation(NewRotation);
}
