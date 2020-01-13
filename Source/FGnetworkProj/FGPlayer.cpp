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
 	
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	//CameraComponent->bUsePawnControlRotation = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(GetCapsuleComponent());

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

}

// Called to bind functionality to input
void AFGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFGPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFGPlayer::LookUpAtRate);
}

void AFGPlayer::Jump()
{

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
	GEngine->AddOnScreenDebugMessage(-2, 5, FColor::Red, TEXT("helo u turned"));
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFGPlayer::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

