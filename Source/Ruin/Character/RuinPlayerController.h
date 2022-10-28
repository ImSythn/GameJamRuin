// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"
#include "RuinCharacter.h"
#include "GameFramework/PlayerController.h"
#include "RuinPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RUIN_API ARuinPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<ARuinCharacter> PossessedRuinCharacter;
	
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	void MoveForwardCallback(float AxisValue);
	void MoveRightCallback(float AxisValue);
	void LookUpCallback(float AxisValue);
	void TurnCallback(float AxisValue);

	void JumpCallback();
	void StopJumpCallback();
	void CrouchCallback();
	void UnCrouchCallback();
};
