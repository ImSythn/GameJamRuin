// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.


#include "Ruin/GameInstance/RuinGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Ruin/LogCategories.h"

// Sets default values
URuinGameInstance::URuinGameInstance()
{
	// Sets default session name for the server
	SessionName = "Ruin Session";
}

void URuinGameInstance::Init()
{
	Super::Init();

	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (!SessionInterface.IsValid())
		{
			UE_LOG(LogServer, Warning, TEXT("SessionInterface is not valid"));
			return;
		}

		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &URuinGameInstance::OnCreateSessionComplete);
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &URuinGameInstance::OnFindSessionComplete);
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &URuinGameInstance::OnJoinSessionComplete);
	}
}

void URuinGameInstance::OnCreateSessionComplete(FName SName, bool bSucceeded)
{
	if (!bSucceeded)
	{
		UE_LOG(LogServer, Warning, TEXT("OnCreateSessionComplete failed"));
		return;
	}
	
	GetWorld()->ServerTravel("/Game/Core/Levels/Level?listen");
}

void URuinGameInstance::OnFindSessionComplete(bool bSucceeded)
{
	if (!bSucceeded)
	{
		UE_LOG(LogServer, Warning, TEXT("OnFindSessionComplete failed"));
		return;
	}
	
	TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;

	if (SearchResults.Num())
	{
		SessionInterface->JoinSession(0, SessionName, SearchResults[0]);
	}
	
}

void URuinGameInstance::OnJoinSessionComplete(FName SName, EOnJoinSessionCompleteResult::Type Result)
{
	if(Result != EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogServer, Warning, TEXT("OnJoinSessionComplete failed"));
		return;
	}
	
	if (APlayerController* PlayerController = GetFirstLocalPlayerController())
	{
		FString JoinAddress;
		
		if (!SessionInterface->GetResolvedConnectString(SessionName, JoinAddress)) return;
			
		PlayerController->ClientTravel(JoinAddress, TRAVEL_Absolute);
	}
}

void URuinGameInstance::CreateSession()
{
	UE_LOG(LogServer, Display, TEXT("CreateServer"));
	
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 4;

	SessionInterface->CreateSession(0, SessionName, SessionSettings);
}

void URuinGameInstance::JoinSession()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if(SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL";
		SessionSearch->MaxSearchResults = 10000;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

// When force quit game, handle LeaveSession()
void URuinGameInstance::BeginDestroy()
{
	LeaveSession();
	
	Super::BeginDestroy();
}

void URuinGameInstance::LeaveSession()
{
	UE_LOG(LogServer, Display, TEXT("LeaveSession"));

	// Check if a session with the specified session name exists, if so destroy it.
	if(SessionInterface && SessionInterface->GetNamedSession(SessionName))
	{
		UE_LOG(LogServer, Warning, TEXT("Destroy the session now"));
		SessionInterface->DestroySession(SessionName);
		
		SwapHost();
	}
}

// Swap hosts if the host left the session.
void URuinGameInstance::SwapHost()
{
}
