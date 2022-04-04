// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "GameDetail/UIBase.h"
#include "Fastest.h"

AMyHUD::AMyHUD()
{
    static ConstructorHelpers::FObjectFinder<UTexture2D> CROSSHAIR_OBJ(TEXT("Texture2D'/Game/FirstHourUMG/Character/Textures/FirstPersonCrosshair.FirstPersonCrosshair'"));
    if(CROSSHAIR_OBJ.Succeeded())
    {
        CrosshairTex = CROSSHAIR_OBJ.Object;
    }

    static ConstructorHelpers::FClassFinder<UUIBase> WIDGET_OBJ(TEXT("WidgetBlueprint'/Game/UI/UI_MainWidget.UI_MainWidget_C'"));
    if(WIDGET_OBJ.Succeeded())
    {
        HUDWidgetClass = WIDGET_OBJ.Class;
    }
}

void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    const FVector2D Center(Canvas->ClipX * 0.5f - CrosshairSize.X * 0.5f, Canvas->ClipY * 0.5f - CrosshairSize.Y * 0.5f);

    const FVector2D CrosshairDrawPosition((Center.X),
        (Center.Y + 20.0f));

    // draw the crosshair
    FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, CrosshairSize, FLinearColor::White);
    TileItem.BlendMode = SE_BLEND_Translucent;
    Canvas->DrawItem(TileItem);
}

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    if(HUDWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUIBase>(GetWorld(), HUDWidgetClass);

        if(CurrentWidget)
        {
            CurrentWidget->AddToViewport();
        }
    }
}
