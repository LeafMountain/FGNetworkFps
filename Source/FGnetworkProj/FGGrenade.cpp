#include "FGGrenade.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include <TimerManager.h>
#include <Engine/World.h>
#include "Engine/Engine.h"
#include "FGnetworkProj/FGPlayer.h"
#include "HealthSystem/HealthComponent.h"
#include "Components/PrimitiveComponent.h"

AFGGrenade::AFGGrenade()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));   
    Collider->SetSphereRadius(DamageRadius);
	Collider->bHiddenInGame = false;

	RootComponent = Mesh;
	Collider->SetupAttachment(Mesh);

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AFGGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetOwner()->Role == ROLE_Authority)
	{
		Multicast_UpdatePosition(GetActorLocation());
	}
}

void AFGGrenade::Explode()
{
	Multicast_Explosion();

	if (GetOwner()->Role == ROLE_Authority)
	{
		Collider->GetOverlappingActors(OverlappingActors);
		for (int i = 0; i < OverlappingActors.Num(); i++)
		{
			UHealthComponent* PlayerHealth = Cast<UHealthComponent>(OverlappingActors[i]->GetComponentByClass(UHealthComponent::StaticClass()));
			if (PlayerHealth != nullptr)
			{
				PlayerHealth->TakeDamage(Damage);
			}

			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((OverlappingActors[i]->GetRootComponent()));
			if (MeshComp != Mesh && MeshComp)
			{
				Multicast_PushBack(MeshComp);
			}
		}
	}

    Destroy();
}

void AFGGrenade::ThrowGrenade(FVector ThrowDirection)
{
	Mesh->AddImpulse(ThrowDirection * ThrowForce);
	GetWorldTimerManager().SetTimer(ExplosionTimer, this, &AFGGrenade::Explode, ExplosionDelay, false);
}

void AFGGrenade::Multicast_Explosion_Implementation()
{
	BP_Explosion();
}

void AFGGrenade::Server_UpdatePosition_Implementation(FVector Position)
{
	Multicast_UpdatePosition(Position);
}

void AFGGrenade::Multicast_UpdatePosition_Implementation(FVector Position)
{
	SetActorLocation(Position);
}

void AFGGrenade::Multicast_PushBack_Implementation(UStaticMeshComponent * MeshComponent)
{
	MeshComponent->AddRadialImpulse(GetActorLocation(), PushBackRadius, PushBackForce, ERadialImpulseFalloff::RIF_Linear, true);
}