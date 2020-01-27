#pragma once

#include "Components/ActorComponent.h"
#include "UserComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FGNETWORKPROJ_API UUserComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUserComponent();

	class IUseable* Useable;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class IUseable> test;

	UFUNCTION(BlueprintCallable)
	void Use();
};