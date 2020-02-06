// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreSystem.h"
#include "ScoreComponent.h"
#include <Engine/Engine.h>

UScoreSystem::UScoreSystem()
{
}

void UScoreSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UScoreSystem::Deinitialize()
{
	Super::Deinitialize();
}

void UScoreSystem::SetScore(const FString name, const FString key, const int value)
{
	ScoreMap.FindOrAdd(name).Add(key, value);
}

void UScoreSystem::AddScore(const FString name, const FString key, const int value /*= 1*/)
{
	SetScore(name, key, value + GetScore(name, key));
}

int UScoreSystem::GetScore(const FString name, const FString key)
{
	return (ScoreMap[name])[key];
}

//TArray<FString, TArray<FString, int>> UScoreSystem::GetAllScores()
//{
//	ScoreMap.GetKeys();
//}

TArray<FString> UScoreSystem::GetScores(const FString name, const FString key)
{
	TArray<FString> temp;

	return temp;
}

TArray<FString> UScoreSystem::GetPlayerNames()
{
	TArray<FString> Names;

	for (auto It = ScoreComponents.CreateConstIterator(); It; ++It)
	{
		UScoreComponent* ScoreComponent = *It;
		Names.Add(ScoreComponent->GetName());
	}

	return Names;
}

void UScoreSystem::AddScoreComponent(UScoreComponent* Component)
{
	if (ScoreComponents.Contains(Component) == false)
	{
		GEngine->AddOnScreenDebugMessage(-2, 10.0f, FColor::Green, FString::Printf(TEXT("%s joined the game."), *Component->GetName()));
		ScoreComponents.Add(Component);
		OnPlayerJoined.Broadcast(Component);
	}
}

void UScoreSystem::RemoveScoreComponent(UScoreComponent* Component)
{
	ScoreComponents.Remove(Component);
}