// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGNETWORKPROJ_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	// UPROPERTY(Replicated)
	float CurrentHealth = 0.f;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerLowerHealth(float Value);
	bool ServerLowerHealth_Validate(float Value);
	void ServerLowerHealth_Implementation(float Value);

	UFUNCTION(BlueprintPure)
	float GetHealth();

	UFUNCTION()
	void LowerHealth(float Value);

	UPROPERTY(EditAnywhere)
	float InitialHealth = 1.f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	void TakeDamage(float Value);
};
