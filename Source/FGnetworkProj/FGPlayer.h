// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FGPlayer.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class UCameraComponent;
class URespawnComponent;
class UHealthComponent;
class AFGGrenade;

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

UCLASS()
class FGNETWORKPROJ_API AFGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	
	AFGPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, Category = Replication)
	float InterpSpeed = 3.5f;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float WeaponRange = 30000.f;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	float WeaponDamage = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	float HeadShootDamage = 500.f;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Body;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Head;

protected:

	UFUNCTION(Server, Reliable)
	void Server_UpdatePositionAndRotation(FRotator Rotation, FVector Location, float DeltaTime);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdatePositionAndRotation(FRotator Rotation, FVector Location, float DeltaTime);

	UFUNCTION(Server, Reliable)
	void Server_FireWeapon();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_FireWeapon(FHitResult Hit);

	virtual void BeginPlay() override;
	UPROPERTY(VisibleDefaultsOnly, Category = CameraComponent)
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleDefaultsOnly)
	UHealthComponent* HealthComponent;
	UPROPERTY(VisibleDefaultsOnly)
	URespawnComponent* RespawnComponent;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AFGGrenade> Grenades;

public:

	void FireWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float val);

	void MoveRight(float val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void TakeDamage(float Damage);

	void ThrowGrenade();

	void Die();
};
