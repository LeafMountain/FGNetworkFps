#include "ScoreComponent.h"
#include "Blueprint/UserWidget.h"
#include "ScoreSystem.h"
#include "Net/UnrealNetwork.h"

UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = false;

	if (Name.IsEmpty())
	{
		FString TempName = TEXT("Name#");
		TempName.AppendInt(FMath::RandRange(0, 9999));
		SetName(TempName);
	}

	ScoreSystem = GetWorld()->GetGameInstance()->GetSubsystem<UScoreSystem>();
	ScoreSystem->AddScoreComponent(this);

}

void UScoreComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ScoreSystem->RemoveScoreComponent(this);
	Super::EndPlay(EndPlayReason);
}

void UScoreComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UScoreComponent, Name);
}

void UScoreComponent::SetScore(const FString key, const int value)
{
	ScoreMap.Add(key, value);
}

void UScoreComponent::AddScore(const FString key, int Value /*= 1*/)
{
	// Score Map might not have that value
	int OldScore = ScoreMap.Contains(key) ? ScoreMap[key] : 0;
	ScoreMap.Add(key, OldScore + Value);
}

int UScoreComponent::GetScore(const FString key)
{
	return ScoreMap[key];
}

void UScoreComponent::ShowScore()
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

void UScoreComponent::SetName(const FString& NewName)
{
	Multicast_SetName(NewName);
}

void UScoreComponent::Server_SetName_Implementation(const FString& NewName)
{
	Multicast_SetName(NewName);
}

void UScoreComponent::Multicast_SetName_Implementation(const FString& NewName)
{
	Name = NewName;
}
