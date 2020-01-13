// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGNETWORKPROJ_API UDamagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// UFUNCTION()
	void OnOverlapBegin(AActor* Actor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	float DamageValue = -1.f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
