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
#include <Engine/CollisionProfile.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Engine/World.h>


// Sets default values
AFGPlayer::AFGPlayer()
{
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
 	
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();

	CurrentAmountGrenades = MaxAmountGrenades;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 0;
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->bUsePawnControlRotation = true;

	BodyHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BodyHitBox"));
	BodyHitbox->SetupAttachment(GetCapsuleComponent());
	BodyHitbox->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	BodyHitbox->SetRelativeLocation(FVector(0.f, 0.f, -7.f));
	BodyHitbox->SetCapsuleHalfHeight(62.f);

	HeadHitbox = CreateDefaultSubobject<USphereComponent>(TEXT("HeadHitBox"));
	HeadHitbox->SetupAttachment(RootComponent);
	HeadHitbox->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	HeadHitbox->SetupAttachment(GetMesh(), FName(TEXT("head")));
	HeadHitbox->SetRelativeLocation(FVector(0.f, 0.f, 160.f));
	HeadHitbox->SetSphereRadius(17.f);

	Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	Gun->SetupAttachment(CameraComponent);
	Gun->SetCollisionProfileName(TEXT("NoCollision"));
	Gun->SetRelativeLocation(FVector(7.f, 0.f,-34.f));
	Gun->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(Gun);
	MuzzleLocation->SetRelativeLocation(FVector(0.f, 60.f, 11.f));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	RespawnComponent = CreateDefaultSubobject<URespawnComponent>(TEXT("RespawnComponent"));

	SetReplicateMovement(false);
}

void AFGPlayer::Server_UpdateCameraRotation_Implementation(float Rate)
{
	Multicast_UppdateCameraRotation(Rate);
}

void AFGPlayer::Multicast_UppdateCameraRotation_Implementation(float Rate)
{
	if (GetLocalRole() == ROLE_Authority || GetLocalRole() == ROLE_SimulatedProxy)
	{
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AFGPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled())
		GetMesh()->SetVisibility(false);
}

void AFGPlayer::FireWeapon()
{
	Server_FireWeapon(CameraComponent->GetForwardVector());
}

void AFGPlayer::Server_FireWeapon_Implementation(const FVector ForwardDirection)
{
	//TODO remake this function

	FHitResult Hit;
	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);
	

	if (GetWorld()->LineTraceSingleByChannel(Hit, CameraComponent->GetComponentLocation(),
		GetActorLocation() + ForwardDirection*WeaponRange, ECC_Pawn, CollisionParams))
	{
		//GEngine->AddOnScreenDebugMessage(-2, 5, FColor::Red, FString::Printf(TEXT("%s"), *Hit.Actor->GetName()));

		FHitResult WhatBodyPartHit;
		FCollisionQueryParams Cp;

		Cp.AddIgnoredActor(this);
		Cp.AddIgnoredComponent(Hit.GetComponent());

		if (GetWorld()->LineTraceSingleByChannel(WhatBodyPartHit, CameraComponent->GetComponentLocation(),
			GetActorLocation() + ForwardDirection * WeaponRange, ECC_Pawn, Cp))
		{
			AFGPlayer* HitPlayer = Cast<AFGPlayer>(Hit.Actor);
			if (HitPlayer)
			{
				GEngine->AddOnScreenDebugMessage(-2, 5, FColor::Red, FString::Printf(TEXT("%s"), *WhatBodyPartHit.GetComponent()->GetCollisionProfileName().ToString()));
				float FinalDamage = 0;
				if (WhatBodyPartHit.GetComponent() == HitPlayer->BodyHitbox)
				{
					FinalDamage = WeaponDamage;
				}
				else if (WhatBodyPartHit.GetComponent() == HitPlayer->HeadHitbox)
				{
					FinalDamage = HeadShootDamage;
				}

				if (UHealthComponent* otherHealth = (UHealthComponent*)HitPlayer->GetComponentByClass(UHealthComponent::StaticClass()))
				{
					//HitPlayer->TakeDamage(FinalDamage);
					otherHealth->TakeDamage(FinalDamage);
					OnDamageDone(FinalDamage);
				}
			}
		}
		Multicast_FireWeapon(Hit);
	}
}

void AFGPlayer::Multicast_FireWeapon_Implementation(FHitResult Hit)
{
	//TODO make weapon fire visuals here
	//DrawDebugLine(GetWorld(), GetActorLocation(),GetActorLocation() + CameraComponent->GetForwardVector()*WeaponRange, FColor::Purple, false, 1, 0, 1);

	if (GetLocalRole() == ROLE_Authority)
	{
		return;
	}

	BP_MuzzleFlash();
	BP_HitLocation(Hit);
}

void AFGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocallyControlled())
	{
		if (GetLocalRole() == ROLE_Authority)
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
	//AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

	if (IsLocallyControlled())
	{
		if ( GetLocalRole() == ROLE_Authority)
		{
			Multicast_UppdateCameraRotation(Rate);
		}
		else
			Server_UpdateCameraRotation(Rate);
	}
}

void AFGPlayer::TakeSomeDamage(float Damage)
{
	//HealthComponent->TakeDamage(Damage);
}

void AFGPlayer::ThrowGrenade()
{
    if (IsLocallyControlled())
    {
		Server_ThrowGrenade(CameraComponent->GetForwardVector());
    }
}

void AFGPlayer::Server_ThrowGrenade_Implementation(FVector ThrowDirection)
{
	if (CurrentAmountGrenades > 0)
	{
		Multicast_ThrowGrenade(ThrowDirection);
		CurrentAmountGrenades--;
	}
}

void AFGPlayer::Multicast_ThrowGrenade_Implementation(FVector ThrowDirection)
{
	if (GetLocalRole() != ROLE_Authority)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

    AFGGrenade* Grenade = GetWorld()->SpawnActor<AFGGrenade>(Grenades, GetActorLocation() + CameraComponent->GetForwardVector() * 100, GetActorRotation(), SpawnParams);
    Grenade->ThrowGrenade(ThrowDirection);
}

void AFGPlayer::Die()
{
	Multicast_Death();

	if (IsLocallyControlled())
	{
		SpringArm->TargetArmLength = 600;

		GetMesh()->SetVisibility(true);
		Gun->SetVisibility(false);
		DisableInput(Cast<APlayerController>(GetController()));
	}
}

void AFGPlayer::Respawn()
{
	SpringArm->TargetArmLength = 0;
	SetActorEnableCollision(true);
	Gun->SetVisibility(true);
	EnableInput(Cast<APlayerController>(GetController()));
	RespawnComponent->RespawnPlayer(this);
	CurrentAmountGrenades = MaxAmountGrenades;

	GetMesh()->PlayAnimation(IdleAnim, false);

	if (IsLocallyControlled())
		GetMesh()->SetVisibility(false);
}

void AFGPlayer::Multicast_Death_Implementation()
{
	GetMesh()->PlayAnimation(DeathAnim, false);
	SetActorEnableCollision(false);
	Gun->SetVisibility(false);

	//PlayAnimMontage(DeathAnimMontage);

	GetWorldTimerManager().SetTimer(RespawnTimer, this, &AFGPlayer::Respawn, 5.f, false);
}

void AFGPlayer::Server_UpdatePositionAndRotation_Implementation(FRotator Rotation, FVector Location, float DeltaTime)
{
	Multicast_UpdatePositionAndRotation(Rotation, Location, DeltaTime);
}

void AFGPlayer::Multicast_UpdatePositionAndRotation_Implementation(FRotator Rotation, FVector Location, float DeltaTime)
{
	if (GetLocalRole() == ROLE_Authority || GetLocalRole() == ROLE_SimulatedProxy)
	{
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), Rotation, DeltaTime, InterpSpeed));
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), Location, DeltaTime, InterpSpeed));
	}
}