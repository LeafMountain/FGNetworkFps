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
    Collider->SetSphereRadius(100);
	Collider->bHiddenInGame = false;

	RootComponent = Mesh;
	Collider->SetupAttachment(Mesh);

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
}

void AFGGrenade::Explode()
{
    BP_Explosion();

	if (Role != ROLE_Authority)
		return;

	Collider->GetOverlappingActors(OverlappingActors);

	for (int i = 0; i < OverlappingActors.Num(); i++)
	{
		UHealthComponent* PlayerHealth = Cast<UHealthComponent>(OverlappingActors[i]->GetComponentByClass(UHealthComponent::StaticClass()));
		if (PlayerHealth != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-i - 1, 5, FColor::Red, FString::Printf(TEXT("damage")));
			PlayerHealth->TakeDamage(Damage);
		}
	}

    Destroy();
}


void AFGGrenade::ThrowGrenade(FVector ThrowDirection)
{
	Mesh->AddImpulse(ThrowDirection * ThrowForce);
	GetWorldTimerManager().SetTimer(ExplosionTimer, this, &AFGGrenade::Explode, ExplosionDelay, false);
}
