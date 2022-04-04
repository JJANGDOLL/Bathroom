// Fill out your copyright notice in the Description page of Project Settings.


#include "ActEngine.h"
#include "Utils/MyUtils.h"

// Sets default values
AActEngine::AActEngine()
{
	Helpers::CreateComponent(this, &DefaultSceneRoot, "DefaultScene");

	Helpers::CreateComponent(this, &InteractLocation, "InteractLoc", DefaultSceneRoot);
	InteractLocation->SetRelativeLocationAndRotation(FVector(30.f, 0.f, 0.f), FRotator(0.f, 90.f, 0.f));

	Helpers::CreateComponent(this, &TakeLocation, "TakeLocation", InteractLocation);
	TakeLocation->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -60.f), FRotator(0.f, 0.f, 0.f));
}

