// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/WorldObjectBase.h"
#include "Curves/CurveFloat.h"
#include "Components/TimelineComponent.h"
#include "Interfaces/Switch.h"
#include "CeillingLamp.generated.h"

/**
 * 
 */
UCLASS()
class FASTEST_API ACeillingLamp : public AWorldObjectBase, public ISwitch
{
	GENERATED_BODY()
	
public:
	ACeillingLamp();

	UPROPERTY(VisibleInstanceOnly, Category = Lamp, Meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* LampMesh;

	UPROPERTY(VisibleInstanceOnly, Category = Lamp, Meta = (AllowPrivateAccess = true))
	class UPointLightComponent* Light;

	UPROPERTY(VisibleInstanceOnly, Category=Lamp, Meta = (AllowPrivateAccess = true))
	bool bSwitch = true;

	UCurveFloat* BlinkCurve;
	FTimeline BlinkTimeline;
	float SmoothTimelineLength;

	UFUNCTION()
	void BlinkLamp(float Value);

	virtual void Tick(float DeltaTime) override;

	virtual void Off() override;
	virtual void On() override;

	bool bOn = true;

protected:
	virtual void BeginPlay() override;

};
