#pragma once

#include "GameFramework/Actor.h"
#include "Useable.h"
#include "Weapon.generated.h"

UCLASS()
class FGNETWORKPROJ_API AWeapon : public AActor, public IUseable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Useable")
	void Use();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Useable")
	void OnUse();
};
