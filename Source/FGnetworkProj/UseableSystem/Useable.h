#pragma once

#include "UObject/Interface.h"
#include "Useable.generated.h"

UINTERFACE(Blueprintable)
class FGNETWORKPROJ_API UUseable : public UInterface
{
	GENERATED_BODY()
};

class FGNETWORKPROJ_API IUseable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Useable")
	void Use();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Useable")
	void OnUse();
};
