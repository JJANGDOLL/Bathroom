// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/StaticMesh.h"
#include "Components/PointLightComponent.h"
#include "Fastest.h"
#include "Kismet/GameplayStatics.h"
#include "GameDetail/MyGameModeBase.h"
#include "WorldLightBase.h"

AWorldLightBase::AWorldLightBase()
{
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

void AWorldLightBase::BlinkLamp(float Value)
{
	if(!bSwitch)
		return;

	if(bOn)
		Light->SetIntensity(LIGHT_INTENSITY * Value);
	else
		Light->SetIntensity(0.f);
}

void AWorldLightBase::Tick(float DeltaTime)
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

void AWorldLightBase::Off()
{
	bOn = false;
}

void AWorldLightBase::On()
{
	bOn = true;
	BlinkType = EObjectBlink::NORMAL;
	TimeSwitchedOn = gameMode->GetPlayedTime();
}

void AWorldLightBase::BeginPlay()
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