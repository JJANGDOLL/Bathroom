// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/Scene.h"
#include "PPZoomVolume.generated.h"

/**
 * 
 */
UCLASS()
class FASTEST_API APPZoomVolume : public APostProcessVolume
{
	GENERATED_BODY()

	APPZoomVolume();

public:
	FWeightedBlendable* WB_Hightlight;
	FWeightedBlendable* WB_Blur;

	void ZoomIn();
	void ZoomOut();
};
