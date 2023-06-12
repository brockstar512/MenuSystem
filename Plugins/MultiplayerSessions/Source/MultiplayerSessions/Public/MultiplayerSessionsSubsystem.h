// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionsSubsystem.generated.h"
/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	public:
		UMultiplayerSessionsSubsystem();

		//To Handle session functionality. The menu class will call this

		void CreateSession(int32 NumPublicConnections, FString MatchType);
		void FindSessions(int32 MaxSearchResults);
		void JoinSession(const FOnlineSessionSearchResult& SessionResult);
		void DestroySession();
		void StartSession();

	protected:
		//internal callbacks for the delegates we'll add to the online session interface delegate list
		//these sone need to be called outside of this class

		void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
		void OnFindSessionsComplete(bool bWasSuccessful);
		void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
		void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
		void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);




	private:
		IOnlineSessionPtr SessionInterface;
		TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
		//To add to the online session interface delegate list
		//we'll bind our  Multiplayer subsystem internal callbacks to these.

		FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
		FDelegateHandle CreateSessionCompleteDelegateHandle;
		FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
		FDelegateHandle FindSessionCompleteDelegateHandle;
		FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
		FDelegateHandle JoinSessionCompleteDelegateHandle;
		FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
		FDelegateHandle DestroySessionCompleteDelegateHandle;
		FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
		FDelegateHandle StartSessionCompleteDelegateHandle;


};
