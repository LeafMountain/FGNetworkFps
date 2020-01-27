#include "FGnetworkProjScoreComponent.h"
#include "Blueprint/UserWidget.h"

UFGnetworkProjScoreComponent::UFGnetworkProjScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFGnetworkProjScoreComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = false;
}

void UFGnetworkProjScoreComponent::SetScore(const FString key, const int value)
{
	ScoreMap.Add(key, value);
}

void UFGnetworkProjScoreComponent::AddScore(const FString key, int Value /*= 1*/)
{
	// Score Map might not have that value
	int OldScore = ScoreMap.Contains(key) ? ScoreMap[key] : 0;
	ScoreMap.Add(key, OldScore + Value);
}

int UFGnetworkProjScoreComponent::GetScore(const FString key)
{
	return ScoreMap[key];
}

void UFGnetworkProjScoreComponent::ShowScore()
{
	//if (ScorePanel == nullptr)
	//{
	//	ScorePanel = CreateWidget<Widget.Class>(GetWorld(), UUserWidget::StaticClass());
	//	ScorePanel->AddToViewport(0);
	//}

	//if (ScorePanel->GetIsVisible())
	//{
	//	ScorePanel->SetVisibility(ESlateVisibility::Hidden);
	//}
	//else
	//{
	//	ScorePanel->SetVisibility(ESlateVisibility::Visible);
	//}
}
