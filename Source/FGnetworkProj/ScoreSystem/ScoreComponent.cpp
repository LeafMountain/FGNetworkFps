#include "ScoreComponent.h"
#include "Blueprint/UserWidget.h"
#include "ScoreSystem.h"
#include "Net/UnrealNetwork.h"
#include <Engine/Engine.h>

UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();

	ENetRole role = GetOwner()->GetLocalRole();

	if (GetOwner()->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		ScoreSystem = GetWorld()->GetGameInstance()->GetSubsystem<UScoreSystem>();
		ScoreSystem->AddScoreComponent(this);
	}

	GetPlayerIndex();
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

	DOREPLIFETIME( UScoreComponent, Name);
	DOREPLIFETIME( UScoreComponent, PlayerNetIndex );
	DOREPLIFETIME( UScoreComponent, PlayerCount );
}

void UScoreComponent::TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	GEngine->AddOnScreenDebugMessage( PlayerNetIndex, 0, FColor::Red, FString::Printf( TEXT( "%s score: %i" ), *Name, GetScore("kills") ));
}

void UScoreComponent::SetScore(const FString key, const int value)
{
	ScoreMap.Add(key, value);
}

void UScoreComponent::AddScore(const FString key, int Value /*= 1*/)
{
	int OldScore = ScoreMap.Contains(key) ? ScoreMap[key] : 0;
	ScoreMap.Add(key, OldScore + Value);
}

int UScoreComponent::GetScore(const FString key)
{
	if ( ScoreMap.Contains( key ) )
	{
		return ScoreMap[key];
	}

	return 0;
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

void UScoreComponent::GetPlayerIndex()
{
	Server_GetPlayerIndex();
}

void UScoreComponent::Multicast_GetPlayerIndex_Implementation( int IndexFromServer )
{
	PlayerNetIndex = IndexFromServer;
	PlayerCount = IndexFromServer;
	SetName( FString::Printf( TEXT( "Player#%i" ), PlayerNetIndex ));
}

void UScoreComponent::Server_GetPlayerIndex_Implementation()
{
	PlayerCount += 1;
	Multicast_GetPlayerIndex(PlayerCount);
}
