#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"

class APlayerStart;

UCLASS()
class FGNETWORKPROJ_API URespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URespawnComponent();

	void RespawnPlayer(AActor* Player);

protected:
	TArray<AActor*> SpawnPoints;
};