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
class USkeletalMeshComponent;
class USceneComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	float WeaponRange = 30000.f;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	float WeaponDamage = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	float HeadShootDamage = 500.f;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Gun;

	UPROPERTY(VisibleDefaultsOnly, Category = Hitbox)
	class USphereComponent* HeadHitbox;

	UPROPERTY(VisibleDefaultsOnly, Category = Hitbox)
	UCapsuleComponent* BodyHitbox;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* MuzzleLocation;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void BP_MuzzleFlash();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_HitLocation(FHitResult hit);

	UFUNCTION(Server, Reliable)
	void Server_UpdateCameraRotation(float Rate);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UppdateCameraRotation(float Rate);

	UFUNCTION(Server, Reliable)
	void Server_UpdatePositionAndRotation(FRotator Rotation, FVector Location, float DeltaTime);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdatePositionAndRotation(FRotator Rotation, FVector Location, float DeltaTime);

	UFUNCTION(Server, Reliable)
	void Server_FireWeapon(FVector ForwardDirection);

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

    UFUNCTION(Server, Reliable)
    void Server_ThrowGrenade(FVector ThrowDirection);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_ThrowGrenade(FVector ThrowDirection);

	UPROPERTY(EditAnywhere)
	int MaxAmountGrenades = 2;

	int CurrentAmountGrenades;

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

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamageDone(float Value);
};
