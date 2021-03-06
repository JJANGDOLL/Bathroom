// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Switch.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USwitch : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FASTEST_API ISwitch
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void On() = 0;
	virtual void Off() = 0;
};
