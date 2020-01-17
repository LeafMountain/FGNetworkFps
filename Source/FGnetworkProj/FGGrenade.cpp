#include "FGGrenade.h"
#include <Components/StaticMeshComponent.h>
#include <Components/CapsuleComponent.h>
#include <TimerManager.h>
#include <Engine/World.h>
#include "Engine/Engine.h"

AFGGrenade::AFGGrenade()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AFGGrenade::Explode()
{
	Destroy();
}

void AFGGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Server_UpdatePositionAndRotation(GetActorLocation(), GetActorRotation());
}

void AFGGrenade::ThrowGrenade(FVector ThrowDirection)
{
	Mesh->AddImpulse(ThrowDirection * 5000);
	GetWorldTimerManager().SetTimer(ExplosionTimer, this, &AFGGrenade::Explode, ExplodeDelay, false);
}

void AFGGrenade::Multicast_UpdatePositionAndRotation_Implementation(FVector Position, FRotator Rotation)
{
	if (Role == ROLE_SimulatedProxy || Role == ROLE_Authority)
	{
		SetActorLocation(Position);
		SetActorRotation(Rotation);
		GEngine->AddOnScreenDebugMessage(-2, 5, FColor::Red, FString::Printf(TEXT("yoyoyo")));
	}
}

void AFGGrenade::Server_UpdatePositionAndRotation_Implementation(FVector Position, FRotator Rotation)
{
	Multicast_UpdatePositionAndRotation(Position, Rotation);
}
