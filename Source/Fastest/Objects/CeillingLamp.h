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
UENUM()
namespace EObjectBlink
{
	enum Type
	{
		NORMAL UMETA(DisplayName = "NORMAL"),
		CRAZY UMETA(DisplayName = "CRAZY")
	};
}

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

	UPROPERTY(EditInstanceOnly, Category=Lamp, Meta = (AllowPrivateAccess = true))
	bool bSwitch = true;

	UPROPERTY(EditInstanceOnly, Category = Lamp, Meta = (AllowPrivateAccess = true))
	TEnumAsByte<EObjectBlink::Type> BlinkType = EObjectBlink::NORMAL;

	UCurveFloat* BlinkCurve;
	UCurveFloat* CrazyBlinkCurve;

	FTimeline BlinkTimeline;
	FTimeline CrazyBlinkTimeline;
	
	float TimeSwitchedOn;

	class AMyGameModeBase* gameMode;


	UFUNCTION()
	void BlinkLamp(float Value);

	virtual void Tick(float DeltaTime) override;

	virtual void Off() override;
	virtual void On() override;

	bool bOn = true;

protected:
	virtual void BeginPlay() override;

};
