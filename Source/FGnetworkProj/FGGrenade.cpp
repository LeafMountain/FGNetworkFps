#include "FGGrenade.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include <TimerManager.h>
#include <Engine/World.h>
#include "Engine/Engine.h"
#include "FGnetworkProj/FGPlayer.h"

AFGGrenade::AFGGrenade()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));    
    Collider->SetSphereRadius(0);
    Collider->OnComponentBeginOverlap.AddDynamic(this, &AFGGrenade::OnOverlapBegin);

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
}

void AFGGrenade::Explode()
{
    BP_Explosion();
    //Collider->SetSphereRadius(1000);
    Destroy();
}

void AFGGrenade::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //if (OtherActor->IsA(AFGPlayer::StaticClass()))
    //    GEngine->AddOnScreenDebugMessage(-2, 5, FColor::Red, FString::Printf(TEXT("HIT!!!")));
}

void AFGGrenade::ThrowGrenade(FVector ThrowDirection)
{
	Mesh->AddImpulse(ThrowDirection * ThrowForce);
	GetWorldTimerManager().SetTimer(ExplosionTimer, this, &AFGGrenade::Explode, ExplodeDelay, false);
}
