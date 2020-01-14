#include "RespawnComponent.h"
#include "HealthSystem/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerStart.h"

URespawnComponent::URespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);
}

void URespawnComponent::RespawnPlayer(AActor* Player)
{
	UHealthComponent* PlayerHealth = Cast<UHealthComponent>(Player->FindComponentByClass(UHealthComponent::StaticClass()));

	if (PlayerHealth != nullptr && SpawnPoints.Num() > 0)
	{
		PlayerHealth->ResetHealth();
		Player->SetActorLocation(SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)]->GetActorLocation());
	}
}