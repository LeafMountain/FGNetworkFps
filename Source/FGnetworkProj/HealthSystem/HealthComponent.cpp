// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include <Engine/Engine.h>
#include <GameFramework/Pawn.h>
#include "Net/UnrealNetwork.h"
#include "FGnetworkProj/FGPlayer.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bReplicates = true;
	SetIsReplicated(true);

	// ...
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	CurrentHealth = InitialHealth;
}

float UHealthComponent::GetHealthPercentage()
{
	return CurrentHealth / InitialHealth;
}

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
	Multicast_LowerHealth(Value);
}

void UHealthComponent::Server_LowerHealth_Implementation(float Value)
{
	Multicast_LowerHealth(Value);
}

void UHealthComponent::Multicast_LowerHealth_Implementation(float Value)
{
	GEngine->AddOnScreenDebugMessage(-3, 5, FColor::Red, FString::Printf(TEXT("%f"), CurrentHealth));
	AFGPlayer* Player = Cast<AFGPlayer>(GetOwner());
	if (Player->IsLocallyControlled() || GetOwnerRole() == ROLE_Authority)
	{
		CurrentHealth -= Value;
		if (CurrentHealth <= 0)
			Player->Die();
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

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}