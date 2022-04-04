// Fill out your copyright notice in the Description page of Project Settings.

//WidgetBlueprint'/Game/UI/UI_ExitDoor.UI_ExitDoor'

#include "ExitDoor.h"
#include "Fastest.h"
#include "Slate/SceneViewport.h"
#include "Character/MyCharacter.h"
#include "Components/Widget.h"
#include "GameDetail/UIBase.h"
#include "GameFramework/PawnMovementComponent.h"

AExitDoor::AExitDoor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/MMSupermarket/SMBuilding/Mesh/SM_Door.SM_Door'"));
	if(SM_FE.Succeeded())
	{
		InteractMesh->SetStaticMesh(SM_FE.Object);
		MeshSize = InteractMesh->GetStaticMesh()->GetBoundingBox().GetSize();
		InteractActor->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = InteractMesh->GetCollisionEnabled();
	}
}

void AExitDoor::OnSelected()
{
    MLCGLOG_S(Display);

    bView = !bView;

    if(bView)
    {
        FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
        FVector2D ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);
        if(ExitUI != nullptr)
        {
            exitUIInst = Cast<UUIBase>(CreateWidget(GetWorld()->GetFirstPlayerController(), ExitUI));
            exitUIInst->AddToViewport();
        }
        AMyCharacter* myPawn = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
        myPawn->DisableMovement();
        GetWorld()->GetFirstPlayerController()->SetMouseLocation(ViewportCenter.X, ViewportCenter.Y);
        GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
        GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
    }
}

void AExitDoor::BeginPlay()
{
    Super::BeginPlay();
}
