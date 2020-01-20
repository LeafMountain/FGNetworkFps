#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGGrenade.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UPrimitiveComponent;

UCLASS()
class FGNETWORKPROJ_API AFGGrenade : public AActor
{
	GENERATED_BODY()
public:
	AFGGrenade();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Collider)
	USphereComponent* Collider;

	UPROPERTY(EditAnywhere)
	float ExplosionDelay = 3;

	UPROPERTY(EditAnywhere)
	float Damage = 1;

    UPROPERTY(EditAnywhere)
    float ThrowForce = 5000;

	FTimerHandle ExplosionTimer;

	void Explode();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Explosion();

	TArray<AActor*> OverlappingActors;

public:
	void ThrowGrenade(FVector ThrowDirection);

};