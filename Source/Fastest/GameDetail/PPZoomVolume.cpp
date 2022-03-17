// Fill out your copyright notice in the Description page of Project Settings.


#include "PPZoomVolume.h"
#include "Materials/MaterialInstanceConstant.h"

APPZoomVolume::APPZoomVolume()
{
    bUnbound = true;

    static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> M_OUTLINE(TEXT("MaterialInstanceConstant'/Game/Materials/PostProcess/M_Highlight_Inst.M_Highlight_Inst'"));
    if(M_OUTLINE.Succeeded())
    {
        AddOrUpdateBlendable(M_OUTLINE.Object, 0.f);
    }

    static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> M_BLUR(TEXT("MaterialInstanceConstant'/Game/Materials/PostProcess/M_BLUR_Inst.M_BLUR_Inst'"));
    if(M_BLUR.Succeeded())
    {
        AddOrUpdateBlendable(M_BLUR.Object, 0.f);
    }

    WB_Hightlight = &Settings.WeightedBlendables.Array[0];
    WB_Hightlight->Weight = 1.f;

    WB_Blur = &Settings.WeightedBlendables.Array[1];
    WB_Blur->Weight = 0.f;
}

void APPZoomVolume::ZoomIn()
{
    WB_Hightlight->Weight = 0.f;
    WB_Blur->Weight = 1.f;
}

void APPZoomVolume::ZoomOut()
{
    WB_Hightlight->Weight = 1.f;
    WB_Blur->Weight = 0.f;
}

