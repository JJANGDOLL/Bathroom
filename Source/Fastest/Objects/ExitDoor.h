// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractActObjectBase.h"
#include "SlateBasics.h"
#include "ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class FASTEST_API AExitDoor : public AInteractActObjectBase
{
	GENERATED_BODY()
	
public:
	AExitDoor();

	virtual void OnSelected() override;

protected:
	virtual void BeginPlay() override;

private:
	bool bView = false;
	TSharedPtr<SWidget> Widget;
};
