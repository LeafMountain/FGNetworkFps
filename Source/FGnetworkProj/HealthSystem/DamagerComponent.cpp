// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagerComponent.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UDamagerComponent::UDamagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UDamagerComponent::OnOverlapBegin);
}


// Called every frame
void UDamagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamagerComponent::OnOverlapBegin(AActor* Actor, AActor* OtherActor)
{
	UHealthComponent* Health = Cast<UHealthComponent>(OtherActor->FindComponentByClass(UHealthComponent::StaticClass()));

	if(Health != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hej"));
		Health->TakeDamage(DamageValue);
	}
}