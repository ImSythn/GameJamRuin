// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "MyPawn.h"

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

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

