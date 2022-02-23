// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractActObjectBase.h"
#include "ToiletBoothDoor.generated.h"

UCLASS()
class FASTEST_API AToiletBoothDoor : public AInteractActObjectBase
{
	GENERATED_BODY()
	
public:
	AToiletBoothDoor();

	virtual void OnSelected() override;

private:
	bool bOpened = false;
};
