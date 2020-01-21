// Fill out your copyright notice in the Description page of Project Settings.


#include "FGPlayer.h"
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Engine/Engine.h>
#include <Engine/World.h>
#include <DrawDebugHelpers.h>
#include "HealthSystem/HealthComponent.h"
#include "RespawnComponent.h"
#include <FGnetworkProj/FGGrenade.h>
#include "FGGrenade.h"

// Sets default values
AFGPlayer::AFGPlayer()
{
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
 	
	CurrentAmountGrenades = MaxAmountGrenades;

	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->bUsePawnControlRotation = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(GetCapsuleComponent());
	Body->SetCollisionProfileName(TEXT("OverlapAll"));

	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(GetCapsuleComponent());
	Head->SetCollisionProfileName(TEXT("OverlapAll"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	RespawnComponent = CreateDefaultSubobject<URespawnComponent>(TEXT("RespawnComponent"));

	SetReplicateMovement(false);
}

void AFGPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFGPlayer::FireWeapon()
{
	FHitResult Hit;
	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + CameraComponent->GetForwardVector()*WeaponRange, FColor::Green, false, 1, 0, 1);

	Server_FireWeapon();
}

void AFGPlayer::Server_FireWeapon_Implementation()
{
	//TODO remake this funktion

	FHitResult Hit;
	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(),
		GetActorLocation() + CameraComponent->GetForwardVector()*WeaponRange, ECC_Pawn, CollisionParams))
	{
		//GEngine->AddOnScreenDebugMessage(-2, 5, FColor::Red, FString::Printf(TEXT("%s"), *Hit.Actor->GetName()));

		FHitResult WhatBodyPartHit;
		FCollisionQueryParams Cp;
		Cp.AddIgnoredComponent(Hit.GetComponent());
		if (GetWorld()->LineTraceSingleByChannel(WhatBodyPartHit, Hit.ImpactPoint, Hit.ImpactPoint + CameraComponent->GetForwardVector() * 100.f, ECC_Visibility, Cp))
		{
			Multicast_FireWeapon(Hit);

			AFGPlayer* HitPlayer = Cast<AFGPlayer>(Hit.Actor);
			if (Hit.GetComponent() == HitPlayer->Body)
			{
				HitPlayer->TakeDamage(WeaponDamage);
			}
			else if(Hit.GetComponent() == HitPlayer->Head)
			{
				HitPlayer->TakeDamage(HeadShootDamage);
			}
		}

	}
}

void AFGPlayer::Multicast_FireWeapon_Implementation(FHitResult Hit)
{
	//TODO make weapon fire visuals here
	DrawDebugLine(GetWorld(), Hit.ImpactPoint, Hit.ImpactPoint + CameraComponent->GetForwardVector()* 100.f, FColor::Purple, false, 1, 0, 1);
}

void AFGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocallyControlled())
	{
		if (Role == ROLE_Authority)
		{
			Multicast_UpdatePositionAndRotation(GetActorRotation(), GetActorLocation(), DeltaTime);
		}
		else
		{
			Server_UpdatePositionAndRotation(GetActorRotation(), GetActorLocation(),DeltaTime);
		}
	}
}

// Called to bind functionality to input
void AFGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFGPlayer::FireWeapon);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("ThrowGrenade", IE_Pressed, this, &AFGPlayer::ThrowGrenade);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFGPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFGPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFGPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFGPlayer::LookUpAtRate);
}

void AFGPlayer::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void AFGPlayer::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void AFGPlayer::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFGPlayer::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFGPlayer::TakeDamage(float Damage)
{
	HealthComponent->TakeDamage(Damage);
}

void AFGPlayer::ThrowGrenade()
{
    if (IsLocallyControlled())
    {
        if (Role == ROLE_Authority)
        {
            Multicast_ThrowGrenade(CameraComponent->GetForwardVector());
        }
        else
        {
            Server_ThrowGrenade(CameraComponent->GetForwardVector());
        }
    }
}

void AFGPlayer::Server_ThrowGrenade_Implementation(FVector ThrowDirection)
{
	if (CurrentAmountGrenades <= 0)
		return;

	CurrentAmountGrenades--;
    Multicast_ThrowGrenade(ThrowDirection);
}

void AFGPlayer::Multicast_ThrowGrenade_Implementation(FVector ThrowDirection)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

    AFGGrenade* Grenade = GetWorld()->SpawnActor<AFGGrenade>(Grenades, GetActorLocation() + CameraComponent->GetForwardVector() * 100, GetActorRotation(), SpawnParams);
    Grenade->ThrowGrenade(ThrowDirection);
}

void AFGPlayer::Die()
{
	RespawnComponent->RespawnPlayer(this);
}

void AFGPlayer::Server_UpdatePositionAndRotation_Implementation(FRotator Rotation, FVector Location, float DeltaTime)
{
	Multicast_UpdatePositionAndRotation(Rotation, Location, DeltaTime);
}

void AFGPlayer::Multicast_UpdatePositionAndRotation_Implementation(FRotator Rotation, FVector Location, float DeltaTime)
{
	if (Role == ROLE_Authority || Role == ROLE_SimulatedProxy)
	{
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), Rotation, DeltaTime, InterpSpeed));
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), Location, DeltaTime, InterpSpeed));
	}
}
