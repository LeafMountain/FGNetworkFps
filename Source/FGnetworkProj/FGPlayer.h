// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FGPlayer.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class UCameraComponent;

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

UCLASS()
class FGNETWORKPROJ_API AFGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFGPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:

	UFUNCTION(Server, Reliable)
		void Server_UpdatePositionAndRotation(FRotator Rotation, FVector Location);

	UFUNCTION(NetMulticast, Reliable)
		void Multicast_UpdatePositionAndRotation(FRotator Rotation, FVector Location);

	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* Body;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* LeftArm;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* RightArm;
	UPROPERTY(VisibleDefaultsOnly, Category = CameraComponent)
	UCameraComponent* CameraComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Jump();

	void MoveForward(float val);

	void MoveRight(float val);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);
};
