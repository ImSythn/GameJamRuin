// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/DefaultPawn.h"

#include "MyPawn.h"
#include "MyPlayerController.h"

#include "RuinGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RUIN_API ARuinGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Override default GameModeBase settings
	void InitGameState() override;

private:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AMyPawn> MyPawnClass = AMyPawn::StaticClass();
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<AMyPlayerController> MyPlayerController = AMyPlayerController::StaticClass();

	
};
