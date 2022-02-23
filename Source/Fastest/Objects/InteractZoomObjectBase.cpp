// Fill out your copyright notice in the Description page of Project Settings.


#include "Fastest.h"
#include "InteractZoomObjectBase.h"
#include "Kismet/GameplayStatics.h"

AInteractZoomObjectBase::AInteractZoomObjectBase()
    : AInteractObjectBase()
{
    InteractType = EObjectInteract::ZOOM;
}

void AInteractZoomObjectBase::OnSelected()
{
    ZoomIn();
}

void AInteractZoomObjectBase::UnSelected()
{
    ZoomOut();
}

void AInteractZoomObjectBase::ZoomIn()
{
    OffFocused();
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    MLCGLOG(Display, TEXT("%s"), *MeshSize.ToString());

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

    FVector ViewLocation = worldLoc + worldDir * (30 + (20 * meshVolumeSize));

    SetActorLocation(ViewLocation);
}

void AInteractZoomObjectBase::ZoomOut()
{
    OnFocused();
    Mesh->SetCollisionEnabled(OriginCollision);
    SetActorLocationAndRotation(OriginLocation, OriginRotator);
}

