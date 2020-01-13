// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FGPlayer.generated.h"

class UStaticMeshComponent;
class UCapsuleComponent;
class UCameraComponent;

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
	// Called when the game starts or when spawned
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
