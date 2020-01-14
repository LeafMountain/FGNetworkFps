// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	CurrentHealth = InitialHealth;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHealthComponent::GetHealth()
{
	return CurrentHealth;
}

void UHealthComponent::LowerHealth(float Value)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		CurrentHealth -= Value;
	}
	else
	{
		ServerLowerHealth(Value);
	}
	
}

bool UHealthComponent::ServerLowerHealth_Validate(float Value)
{
	return CurrentHealth > 0;
}

void UHealthComponent::ServerLowerHealth_Implementation(float Value)
{
	if(GetOwnerRole() == ROLE_Authority)
	{
		LowerHealth(Value);
	}
}

void UHealthComponent::TakeDamage(float Value)
{
	LowerHealth(Value);
}

void UHealthComponent::ResetHealth()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		ServerResetHealth();
	}
}

void UHealthComponent::ServerResetHealth_Implementation()
{
	MulticastResetHealth();
}

void UHealthComponent::MulticastResetHealth_Implementation()
{
	CurrentHealth = InitialHealth;
}
