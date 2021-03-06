// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums/FastestTypes.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FASTEST_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnFocused() = 0;
	virtual void OffFocused() = 0;
	virtual void OnSelected() = 0;
	virtual void UnSelected() = 0;
	virtual EObjectInteract::Type GetInteractObjectType() = 0;
};
