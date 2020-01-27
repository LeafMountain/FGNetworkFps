#include "UserComponent.h"
#include "Useable.h"

UUserComponent::UUserComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUserComponent::Use()
{
	IUseable* UseableInterface = Cast<IUseable>(Useable);
	if (UseableInterface != nullptr)
	{
		//UseableInterface->Execute_Use(test);
	}
}

