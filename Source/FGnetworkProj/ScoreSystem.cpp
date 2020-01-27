// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreSystem.h"

UScoreSystem::UScoreSystem()
{
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
	//TArray<FString, temp> test;
	TArray<TPair<FString, int>> test;

	/*temp[0].

	ScoreMap[name].GetKeys(test);*/
	return temp;
}

TArray<FString> UScoreSystem::GetPlayers()
{
	TArray<FString> names;
	ScoreMap.GetKeys(names);
	return names;
}
