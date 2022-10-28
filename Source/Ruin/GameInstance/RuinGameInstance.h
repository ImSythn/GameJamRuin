// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Engine/GameInstance.h"
#include "RuinGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RUIN_API URuinGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URuinGameInstance();

protected:
	UPROPERTY(EditAnywhere, Category = "Multiplayer")
	FName SessionName;
	
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	IOnlineSessionPtr SessionInterface;
	virtual void Init() override;
	virtual void OnCreateSessionComplete(FName SName, bool bSucceeded);
	virtual void OnFindSessionComplete(bool bSucceeded);
	virtual void OnJoinSessionComplete(FName SName, EOnJoinSessionCompleteResult::Type Result);
	virtual void BeginDestroy() override;

	
	UFUNCTION(BlueprintCallable)
	void CreateSession();

	UFUNCTION(BlueprintCallable)
	void JoinSession();
	
	UFUNCTION(BlueprintCallable)
	void LeaveSession();

	UFUNCTION(BlueprintCallable)
	void SwapHost();
};
