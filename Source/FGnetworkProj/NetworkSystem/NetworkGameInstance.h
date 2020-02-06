#pragma once

#include "Net/UnrealNetwork.h"
#include <Engine/GameInstance.h>
#include "Online.h"
#include "NetworkGameInstance.generated.h"

UCLASS()
class FGNETWORKPROJ_API UNetworkGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UNetworkGameInstance(const FObjectInitializer& ObjectInitializer);

	bool HostSession(const FUniqueNetIdRepl& UserId, FName Sessionname, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	// Find and Search

	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void FindSession(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);
	void OnFindSessionsComplete(bool bWasSuccessful);

	// Joining

	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	bool JoinSession(const FUniqueNetIdRepl& UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// Destroy

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	// Blueprint stuff

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void StartOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void JoinOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void DestroySessionAndLeaveGame();

};