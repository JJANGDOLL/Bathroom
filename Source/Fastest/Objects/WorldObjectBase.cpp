#include "WorldObjectBase.h"

// Sets default values
AWorldObjectBase::AWorldObjectBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWorldObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorldObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

