// Fill out your copyright notice in the Description page of Project Settings.


#include "FGPlayer.h"
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Engine/Engine.h>

// Sets default values
AFGPlayer::AFGPlayer()
{
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
 	
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->bUsePawnControlRotation = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(GetCapsuleComponent());
	Body->SetCollisionProfileName(TEXT("NoCollision"));

	SetReplicateMovement(false);
}

// Called when the game starts or when spawned
void AFGPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocallyControlled() || Role == ROLE_AutonomousProxy)
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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

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
		GEngine->AddOnScreenDebugMessage(-2, 5, FColor::Red, FString::Printf(TEXT("%s"), *GETENUMSTRING("ENetRole", Role)));
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
