// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/WorldObjectBase.h"
#include "Curves/CurveFloat.h"
#include "Components/TimelineComponent.h"
#include "CeillingLamp.generated.h"

/**
 * 
 */
UCLASS()
class FASTEST_API ACeillingLamp : public AWorldObjectBase
{
	GENERATED_BODY()
	
public:
	ACeillingLamp();

	UPROPERTY(VisibleInstanceOnly, Category = Lamp, Meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* LampMesh;

	UPROPERTY(VisibleInstanceOnly, Category = Lamp, Meta = (AllowPrivateAccess = true))
	class UPointLightComponent* Light;

	UCurveFloat* BlinkCurve;
	FTimeline BlinkTimeline;
	float SmoothTimelineLength;

	UFUNCTION()
	void BlinkLamp(float Value);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
