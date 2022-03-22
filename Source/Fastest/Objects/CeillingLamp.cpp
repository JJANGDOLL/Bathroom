// Fill out your copyright notice in the Description page of Project Settings.


// StaticMesh'/Game/OldBrickHouse/Meshes/Props/SM_Lamp_02.SM_Lamp_02'

#include "CeillingLamp.h"
#include "Engine/StaticMesh.h"
#include "Components/PointLightComponent.h"
#include "Fastest.h"
#include "Kismet/GameplayStatics.h"
#include "GameDetail/MyGameModeBase.h"

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
		Light->Intensity = 500.f;
	}

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CF_BLINK(TEXT("CurveFloat'/Game/Timeline/TL_Blink.TL_Blink'"));
	if(CF_BLINK.Succeeded())
	{
		BlinkCurve = CF_BLINK.Object;
	}

	//CurveFloat'/Game/Timeline/TL_CrazyBlink.TL_CrazyBlink'
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CF_CRAZYBLINK(TEXT("CurveFloat'/Game/Timeline/TL_CrazyBlink.TL_CrazyBlink'"));
	if(CF_CRAZYBLINK.Succeeded())
	{
		CrazyBlinkCurve = CF_CRAZYBLINK.Object;
	}
}

void ACeillingLamp::BlinkLamp(float Value)
{
	if(!bSwitch)
		return;

	if(bOn)
		Light->SetIntensity(500.f * Value);
	else
		Light->SetIntensity(0.f);
}

void ACeillingLamp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	if(gameMode != nullptr && int(gameMode->GetPlayedTime()) - TimeSwitchedOn > 13)
	{
		BlinkType = EObjectBlink::CRAZY;
	}

	if(gameMode != nullptr && int(gameMode->GetPlayedTime()) - TimeSwitchedOn > 20)
	{
		bOn = false;
	}

	if(BlinkType == EObjectBlink::NORMAL)
	{
		BlinkTimeline.TickTimeline(DeltaTime);
	}
	else if(BlinkType == EObjectBlink::CRAZY)
	{
		CrazyBlinkTimeline.TickTimeline(DeltaTime);
	}
}

void ACeillingLamp::Off()
{
	bOn = false;
}

void ACeillingLamp::On()
{
	bOn = true;
	BlinkType = EObjectBlink::NORMAL;
	TimeSwitchedOn = gameMode->GetPlayedTime();
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

	if(CrazyBlinkCurve)
	{
		FOnTimelineFloat blinkCallback;

		blinkCallback.BindUFunction(this, FName("BlinkLamp"));
		CrazyBlinkTimeline.AddInterpFloat(CrazyBlinkCurve, blinkCallback);
		CrazyBlinkTimeline.SetLooping(true);
		CrazyBlinkTimeline.Play();
	}
	gameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	TimeSwitchedOn = gameMode->GetPlayedTime();
}

