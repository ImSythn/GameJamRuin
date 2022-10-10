// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "RuinGameModeBase.h"

// Sets default values
void ARuinGameModeBase::InitGameState()
{
	Super::InitGameState();

	// Check if no hard override is active
	if (DefaultPawnClass == ADefaultPawn::StaticClass())
	{
		// Update to custom implementaiton
		DefaultPawnClass = MyPawnClass;
	}
	// Check if no hard override is active
	if (PlayerControllerClass == APlayerController::StaticClass())
	{
		// Update to custom implementaiton
		PlayerControllerClass = MyPlayerController;
	}
}