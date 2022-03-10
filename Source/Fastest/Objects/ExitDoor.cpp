// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitDoor.h"
#include "Fastest.h"
#include "Slate/SceneViewport.h"
#include "Character/MyCharacter.h"

AExitDoor::AExitDoor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/MMSupermarket/SMBuilding/Mesh/SM_Door.SM_Door'"));
	if(SM_FE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_FE.Object);
		MeshSize = Mesh->GetStaticMesh()->GetBoundingBox().GetSize();
		CenterPoint->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = Mesh->GetCollisionEnabled();
	}
}

void AExitDoor::OnSelected()
{
    MLCGLOG_S(Display);

    bView = !bView;

    if(bView)
    {
        GEngine->GameViewport->AddViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), Widget.ToSharedRef(), 1);
        FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
        FVector2D ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);
        GetWorld()->GetFirstPlayerController()->SetMouseLocation(ViewportCenter.X, ViewportCenter.Y);
        GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
        GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
    }
    else
    {
        GEngine->GameViewport->RemoveViewportWidgetForPlayer(GetWorld()->GetFirstLocalPlayerFromController(), Widget.ToSharedRef());
        GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
        GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
    }
}

void AExitDoor::BeginPlay()
{
    Super::BeginPlay();

    
    Widget = SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
        .Padding(5, 5)
        [
            SNew(SButton)
            [
                SNew(STextBlock)
                .Text(FText::FromString(TEXT("1")))
            ]

        ]
    + SHorizontalBox::Slot()
        .Padding(5, 5)
        [
            SNew(SButton)
            [
                SNew(STextBlock)
                .Text(FText::FromString(TEXT("2")))
            ]
        ]
    + SHorizontalBox::Slot()
        .Padding(5, 5)
        [
            SNew(SButton)
            [
                SNew(STextBlock)
                .Text(FText::FromString(TEXT("3")))
            ]
        ]
        ]
    + SVerticalBox::Slot()
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot()
        .Padding(5, 5)
        [
            SNew(SButton)
            [
                SNew(STextBlock)
                .Text(FText::FromString(TEXT("BACK")))
            ]

        ]
        ];
}
