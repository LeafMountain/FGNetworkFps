#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGnetworkProjScoreComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FGNETWORKPROJ_API UFGnetworkProjScoreComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

private:
	TMap<FString, int> ScoreMap;

	//UPROPERTY(EditDefaultsOnly)
	//TSubclassOf<class UUserWidget> Widget;

	//class UUserWidget* ScorePanel;

public:
	UFGnetworkProjScoreComponent();

	UFUNCTION(BlueprintCallable)
		void SetScore(const FString key, const int value);

	UFUNCTION(BlueprintCallable)
		void AddScore(const FString key, int value = 1);

	UFUNCTION(BlueprintCallable)
		int GetScore(const FString key);

	UFUNCTION(BlueprintCallable)
	void ShowScore();
};