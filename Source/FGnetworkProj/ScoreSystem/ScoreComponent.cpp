#include "ScoreComponent.h"
#include "Blueprint/UserWidget.h"
#include "ScoreSystem.h"
#include "Net/UnrealNetwork.h"

UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bReplicates = true;
	SetIsReplicated(true);
}

void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();

	ENetRole role = GetOwner()->GetLocalRole();

	if (Name.IsEmpty() && GetOwner()->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		FString TempName = TEXT("Name#");
		TempName.AppendInt(FMath::RandRange(0, 9999));
		SetName(TempName);
		UE_LOG(LogTemp, Warning, TEXT("Player assigned name: %s"), *TempName);

		ScoreSystem = GetWorld()->GetGameInstance()->GetSubsystem<UScoreSystem>();
		ScoreSystem->AddScoreComponent(this);
	}
}

void UScoreComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ScoreSystem != nullptr)
	{
		ScoreSystem->RemoveScoreComponent(this);
	}

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
	Name = NewName;
	Server_SetName(NewName);
}

void UScoreComponent::Server_SetName_Implementation(const FString& NewName)
{
	Multicast_SetName(NewName);
}

void UScoreComponent::Multicast_SetName_Implementation(const FString& NewName)
{
	if (GetOwnerRole() == ROLE_Authority || GetOwnerRole() == ROLE_SimulatedProxy)
	{
		Name = NewName;
	}
}
