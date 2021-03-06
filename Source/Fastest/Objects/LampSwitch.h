// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractActObjectBase.h"
#include "LampSwitch.generated.h"

/**
 * 
 */
UCLASS()
class FASTEST_API ALampSwitch : public AInteractActObjectBase
{
	GENERATED_BODY()
	
public:
	ALampSwitch();

	UPROPERTY(EditInstanceOnly, Category=LampSwitch)
	TArray<class AWorldLightBase*> Lamps;

	virtual void OnSelected() override;

	bool bOn = true;
};
