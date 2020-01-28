// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScoreSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreEvent, UScoreComponent*, ScoreComponent);

UCLASS()
class FGNETWORKPROJ_API UScoreSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UScoreSystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void SetScore(const FString name, const FString key, const int value);

	UFUNCTION(BlueprintCallable)
	void AddScore(const FString name, const FString key, const int value = 1);

	UFUNCTION(BlueprintCallable)
	int GetScore(const FString name, const FString key);

	//UFUNCTION(BlueprintCallable)
	//TArray<FString, TArray<FString, int>> GetAllScores();
	
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetScores(const FString name, const FString key);

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetPlayerNames();

	void AddScoreComponent(class UScoreComponent* Component);
	void RemoveScoreComponent(class UScoreComponent* Component);

	UPROPERTY(BlueprintAssignable)
	FScoreEvent OnPlayerJoined;

private:
	TMap<FString, TMap<FString, int>> ScoreMap;
	TArray<class UScoreComponent*> ScoreComponents;

};
