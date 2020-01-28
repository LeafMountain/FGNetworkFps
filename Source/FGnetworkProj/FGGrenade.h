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
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	void Server_UpdatePosition(FVector Position);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdatePosition(FVector Position);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Explosion();

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Collider)
	USphereComponent* Collider;

	UPROPERTY(EditAnywhere)
	float DamageRadius = 100;

	UPROPERTY(EditAnywhere)
	float ExplosionDelay = 3;

	UPROPERTY(EditAnywhere)
	float Damage = 1;

    UPROPERTY(EditAnywhere)
    float ThrowForce = 5000;

	UPROPERTY(EditAnywhere)
	float PushBackRadius = 500;

	UPROPERTY(EditAnywhere)
	float PushBackForce = 1000;

	FTimerHandle ExplosionTimer;

	void Explode();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Explosion();

	TArray<AActor*> OverlappingActors;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PushBack(UStaticMeshComponent* MeshComponent);

public:
	void ThrowGrenade(FVector ThrowDirection);

};