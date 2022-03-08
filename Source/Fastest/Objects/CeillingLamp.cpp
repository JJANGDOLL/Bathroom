// Fill out your copyright notice in the Description page of Project Settings.


// StaticMesh'/Game/OldBrickHouse/Meshes/Props/SM_Lamp_02.SM_Lamp_02'

#include "CeillingLamp.h"
#include "Engine/StaticMesh.h"
#include "Components/PointLightComponent.h"
#include "Fastest.h"

ACeillingLamp::ACeillingLamp()
{
	LampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LAMP(TEXT("StaticMesh'/Game/OldBrickHouse/Meshes/Props/SM_Lamp_02.SM_Lamp_02'"));
	LampMesh->SetupAttachment(RootComponent);
	if(SM_LAMP.Succeeded())
	{
		LampMesh->SetStaticMesh(SM_LAMP.Object);
		FVector MeshSize = LampMesh->GetStaticMesh()->GetBoundingBox().GetSize();

		Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
		Light->SetupAttachment(LampMesh);
		Light->SetRelativeLocation(FVector(0.f, 0.f, -MeshSize.Z - 30.f));
		Light->Intensity = 2500.f;
	}

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CF_BLINK(TEXT("CurveFloat'/Game/Timeline/TL_Blink.TL_Blink'"));
	if(CF_BLINK.Succeeded())
	{
		BlinkCurve = CF_BLINK.Object;
	}
}

void ACeillingLamp::BlinkLamp(float Value)
{
	if(bOn)
		Light->SetIntensity(2500.f * Value);
	else
		Light->SetIntensity(25.f);
}

void ACeillingLamp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	BlinkTimeline.TickTimeline(DeltaTime);
}

void ACeillingLamp::Off()
{
	bOn = false;
	MLCGLOG_S(Display);
}

void ACeillingLamp::On()
{
	bOn = true;
	MLCGLOG_S(Display);
}

void ACeillingLamp::BeginPlay()
{
    Super::BeginPlay();

	if(BlinkCurve)
	{
		FOnTimelineFloat blinkCallback;

		blinkCallback.BindUFunction(this, FName("BlinkLamp"));
		BlinkTimeline.AddInterpFloat(BlinkCurve, blinkCallback);
		BlinkTimeline.SetLooping(true);

		BlinkTimeline.Play();
	}
}

