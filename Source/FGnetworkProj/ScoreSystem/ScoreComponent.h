#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FGNETWORKPROJ_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	TMap<FString, int> ScoreMap;

	class UScoreSystem* ScoreSystem;

	UPROPERTY(Replicated)
	FString Name;

	UPROPERTY(Replicated)
	int PlayerNetIndex = -1;

	UPROPERTY(Replicated)
	int PlayerCount = 0;

public:
	UScoreComponent();

	UFUNCTION(BlueprintCallable)
	void SetScore(const FString key, const int value);

	UFUNCTION(BlueprintCallable)
	void AddScore(const FString key, int value = 1);

	UFUNCTION(BlueprintCallable)
	int GetScore(const FString key);

	UFUNCTION(BlueprintPure)
	FString GetName() { return Name; }

	UFUNCTION(BlueprintCallable)
	void SetName(const FString& NewName);

	UFUNCTION(Server, Reliable)
	void Server_SetName(const FString& NewName);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetName(const FString& NewName);
	void Multicast_SetName_Implementation(const FString& NewName);

	UFUNCTION()
	void GetPlayerIndex();

	UFUNCTION(Server, Reliable)
	void Server_GetPlayerIndex();
	void Server_GetPlayerIndex_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_GetPlayerIndex(int IndexFromServer);
	void Multicast_GetPlayerIndex_Implementation( int IndexFromServer );

};