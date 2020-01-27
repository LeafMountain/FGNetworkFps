// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ScoreSystem.generated.h"

UCLASS()
class FGNETWORKPROJ_API UScoreSystem : public USceneComponent
{
	GENERATED_BODY()

public:
	UScoreSystem();

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
	TArray<FString> GetPlayers();

private:
	TMap<FString, TMap<FString, int>> ScoreMap;

};
