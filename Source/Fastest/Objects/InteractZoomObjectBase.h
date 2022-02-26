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

	virtual void SmoothInteract(float Value) override;

	FVector ViewLocation;

protected:
	void ZoomIn(float Value);
	void ZoomOut(float Value);

	virtual void BeginPlay() override;

};
