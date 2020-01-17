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

	UPROPERTY(VisibleDefaultsOnly, Category = Collider)
    USphereComponent* Collider;

	UPROPERTY(EditAnywhere)
	float ExplodeDelay = 3;

    UPROPERTY(EditAnywhere)
    float ThrowForce = 5000;

	FTimerHandle ExplosionTimer;

	void Explode();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_Explosion();

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void ThrowGrenade(FVector ThrowDirection);

};