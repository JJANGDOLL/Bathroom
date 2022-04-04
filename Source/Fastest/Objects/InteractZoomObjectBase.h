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

	TSubclassOf<class UUIBase> InventoryWidgetClass;
	class UUIBase* InventoryUiInst;

	UPROPERTY(VisibleInstanceOnly)
	class USceneCaptureComponent2D* ZoomCapture;

	class UTextureRenderTarget2D* InteractTex;

	UPROPERTY(VisibleInstanceOnly)
	class USpotLightComponent* InteractLight;

	class AActEngine* ActEngine;
	FTransform WorldTransform;
	FTransform CurrentTransform;
	FTransform PivotCurrentTransform;
	FVector CurrentSubLoc;
	FRotator InspectionBeginRot;

	FVector InspectionPivotLoc;
	FVector InteractPivotSize;



	bool bTaking;

	void RotateActor(float Value);


	virtual void ZoomFinished() override;

protected:
	void ZoomIn(float Value);
	void ZoomOut(float Value);

	virtual void BeginPlay() override;

};

