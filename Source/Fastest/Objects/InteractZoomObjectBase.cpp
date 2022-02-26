// Fill out your copyright notice in the Description page of Project Settings.


#include "Fastest.h"
#include "InteractZoomObjectBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathVectorCommon.h"

AInteractZoomObjectBase::AInteractZoomObjectBase()
    : AInteractObjectBase()
{
    InteractType = EObjectInteract::ZOOM;
}

void AInteractZoomObjectBase::OnSelected()
{
    OffFocused();

    FVector2D ViewportSize;
    FVector2D ViewportCenter;
    APlayerController* playerController;

    playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
    ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

    FVector worldLoc;
    FVector worldDir;

    playerController->DeprojectScreenPositionToWorld(ViewportCenter.X, ViewportCenter.Y, worldLoc, worldDir);

    uint32 meshVolumeSize = FMath::FloorToInt((MeshSize.X * MeshSize.Y * MeshSize.Z) / 10000);

    //MLCGLOG(Display, TEXT("%f"), meshVolumeSize);

    ViewLocation = worldLoc + worldDir * (30 + (20 * meshVolumeSize));

    SmoothTimeline.PlayFromStart();
}

void AInteractZoomObjectBase::UnSelected()
{
    OnFocused();
    SmoothTimeline.Reverse();
}

void AInteractZoomObjectBase::SmoothInteract(float Value) 
{
    MLCGLOG_S(Display);
    SetActorLocationAndRotation(FMath::Lerp(OriginLocation, ViewLocation, Value), FMath::Lerp(OriginRotator, GetActorRotation(), Value));
}

void AInteractZoomObjectBase::ZoomIn(float Value)
{
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AInteractZoomObjectBase::ZoomOut(float Value)
{
    Mesh->SetCollisionEnabled(OriginCollision);
    SetActorLocationAndRotation(OriginLocation, OriginRotator);
}

void AInteractZoomObjectBase::BeginPlay()
{
    Super::BeginPlay();
}

