#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGGrenade.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
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

	UPROPERTY(VisibleDefaultsOnly, Category = Collider)
	UCapsuleComponent* Collider;

	UPROPERTY(EditAnywhere)
	float ExplodeDelay = 3;

	FTimerHandle ExplosionTimer;

	void Explode();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SpawnGrenade();

public:

	virtual void Tick(float DeltaTime) override;

	void ThrowGrenade(FVector ThrowDirection);

	UFUNCTION(Server, Reliable)
	void Server_UpdatePositionAndRotation(FVector Position, FRotator Rotation);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdatePositionAndRotation(FVector Position, FRotator Rotation);

};