// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractObjectBase.h"
#include "InteractZoomObjectBase.generated.h"

/**
 * 
 */
UCLASS()
class FASTEST_API AInteractZoomObjectBase : public AInteractObjectBase
{
	GENERATED_BODY()
	
public:
	AInteractZoomObjectBase();

	virtual void OnSelected() override;
	virtual void UnSelected() override;

	UPROPERTY(EditInstanceOnly)
	float Test;

protected:
	void ZoomIn();
	void ZoomOut();
};
