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

private:
	TMap<FString, int> ScoreMap;

	class UScoreSystem* ScoreSystem;

	UPROPERTY(Replicated)
	FString Name;

public:
	UScoreComponent();

	UFUNCTION(BlueprintCallable)
	void SetScore(const FString key, const int value);

	UFUNCTION(BlueprintCallable)
	void AddScore(const FString key, int value = 1);

	UFUNCTION(BlueprintCallable)
	int GetScore(const FString key);

	UFUNCTION(BlueprintCallable)
	void ShowScore();

	UFUNCTION(BlueprintPure)
	FString GetName() { return Name; }

	UFUNCTION(BlueprintCallable)
	void SetName(const FString& NewName);

	UFUNCTION(Server, Reliable)
	void Server_SetName(const FString& NewName);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetName(const FString& NewName);
	void Multicast_SetName_Implementation(const FString& NewName);

};