// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGNETWORKPROJ_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintPure)
	float GetHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	UPROPERTY(Replicated)
	float CurrentHealth = 0.f;

	UFUNCTION(Server, Reliable)
	void Server_LowerHealth(float Value);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_LowerHealth(float Value);

	UFUNCTION(Server, Reliable)
	void ServerResetHealth();
	void ServerResetHealth_Implementation();
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastResetHealth();
	void MulticastResetHealth_Implementation();


	UFUNCTION()
	void LowerHealth(float Value);

	UPROPERTY(EditAnywhere)
	float InitialHealth = 1.f;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	void TakeDamage(float Value);

	void ResetHealth();

	UPROPERTY(BlueprintAssignable)
	FHealthEvent OnHealthDepleted;
};
