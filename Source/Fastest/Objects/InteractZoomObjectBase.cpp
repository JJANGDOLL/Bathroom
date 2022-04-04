// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractZoomObjectBase.h"
#include "Fastest.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathVectorCommon.h"
#include "GameDetail/PPZoomVolume.h"
#include "GameDetail/MyGameModeBase.h"
#include "GameDetail/UIBase.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SpotLightComponent.h"
#include "Components/BillboardComponent.h"
#include "Utils/MyUtils.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerInput.h"


AInteractZoomObjectBase::AInteractZoomObjectBase()
    : AInteractObjectBase()
{
    InteractType = EObjectInteract::ZOOM;

    static ConstructorHelpers::FClassFinder<UUIBase> WIDGET_OBJ(TEXT("WidgetBlueprint'/Game/UI/UI_Interaction.UI_Interaction_C'"));
    if(WIDGET_OBJ.Succeeded())
    {
        InventoryWidgetClass = WIDGET_OBJ.Class;
    }

    static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> INTERACT_OBJ(TEXT("TextureRenderTarget2D'/Game/textures/InteractionCapture.InteractionCapture'"));
    if(INTERACT_OBJ.Succeeded())
    {
        InteractTex = INTERACT_OBJ.Object;
    }

    ZoomCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("ZoomCapture"));
    ZoomCapture->SetupAttachment(RootComponent);
    ZoomCapture->SetRelativeLocationAndRotation(FVector(7.f, 30.f, 0.f), FRotator(0.f, -90.f, 0.f));
    ZoomCapture->TextureTarget = InteractTex;
    ZoomCapture->bCaptureEveryFrame = false;
    ZoomCapture->bCaptureOnMovement = false;

    InteractLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("InteractLight"));
    InteractLight->SetupAttachment(RootComponent);
    InteractLight->SetVisibility(false);
    InteractLight->SetRelativeLocationAndRotation(FVector(200.f, 264.f, 0.f), FRotator(0.f, -135.f, 0.f));

    bTaking = false;

    InputComponent = CreateDefaultSubobject<UInputComponent>("InputComponent");
}

void AInteractZoomObjectBase::OnSelected()
{
    //OffFocused();

    Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetPostProcess()->ZoomIn();

    //FVector2D ViewportSize;
    //FVector2D ViewportCenter;
    //APlayerController* playerController;

    //playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    //ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
    //ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

    //FVector worldLoc;
    //FVector worldDir;

    //playerController->DeprojectScreenPositionToWorld(ViewportCenter.X, ViewportCenter.Y, worldLoc, worldDir);

    //uint32 meshVolumeSize = FMath::FloorToInt((MeshSize.X * MeshSize.Y * MeshSize.Z) / 10000);

    ////MLCGLOG(Display, TEXT("%f"), meshVolumeSize);

    //ViewLocation = worldLoc + worldDir * (30 + (15 * meshVolumeSize));

    ActEngine = Helpers::GetActEngine();
    WorldTransform = GetActorTransform();

    InteractActor->AttachToComponent(InteractPivot, FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true));

    SmoothTimeline.PlayFromStart();

    InventoryUiInst = Cast<UUIBase>(CreateWidget(GetWorld()->GetFirstPlayerController(), InventoryWidgetClass));
    InventoryUiInst->AddToViewport();

    UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->DisableInput(GetWorld()->GetFirstPlayerController());
    EnableInput(GetWorld()->GetFirstPlayerController());
}

void AInteractZoomObjectBase::UnSelected()
{
    OnFocused();
    Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GetPostProcess()->ZoomOut();

    CurrentTransform = GetActorTransform();
    PivotCurrentTransform = InteractPivot->GetComponentTransform();
    CurrentSubLoc = InteractActor->GetRelativeLocation();

    SmoothTimeline.ReverseFromEnd();

    InventoryUiInst->RemoveFromParent();

    UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->EnableInput(GetWorld()->GetFirstPlayerController());
    DisableInput(GetWorld()->GetFirstPlayerController());
}

void AInteractZoomObjectBase::SmoothInteract(float Value) 
{
    //SetActorLocationAndRotation(FMath::Lerp(OriginLocation, ViewLocation, Value), FMath::Lerp(OriginRotator, GetActorRotation(), Value));

    FTransform t1 = (bTaking ? ActEngine->TakeLocation->GetComponentTransform() : WorldTransform);
    FTransform t2 = (AnimDir == ETimelineDirection::Forward ? ActEngine->InteractLocation->GetComponentTransform() : CurrentTransform);

    SetActorTransform(UKismetMathLibrary::TLerp(t1, t2, Value));

    FVector v1 = (AnimDir == ETimelineDirection::Forward ? PivotCurrentTransform.GetLocation() : FVector(0.f, 0.f, 0.f));
    FVector v1r = FMath::Lerp(FVector(0.f, 0.f, 0.f), v1, Value);

    FRotator r1 = (AnimDir == ETimelineDirection::Forward ? InspectionBeginRot : PivotCurrentTransform.Rotator());
    FRotator r1r = FMath::Lerp(FRotator(0.f, 0.f, 0.f), r1, Value);

    FTransform t3 = FTransform(r1r, v1r, FVector(1.f, 1.f, 1.f));

    InteractPivot->SetRelativeTransform(t3);

    FVector v2 = (AnimDir == ETimelineDirection::Forward ? InspectionPivotLoc * -1 : CurrentSubLoc);
    FVector v2r = FMath::Lerp(FVector(0.f, 0.f, 0.f), v2, Value);
    InteractActor->SetRelativeLocation(v2r);
}

void AInteractZoomObjectBase::RotateActor(float Value)
{
    FRotator rot = InteractPivot->GetComponentTransform().Rotator() + FRotator(0.f, 0.f, Value);

    //InteractPivot->SetRelativeRotation(rot);
}

void AInteractZoomObjectBase::ZoomIn(float Value)
{
    InteractMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AInteractZoomObjectBase::ZoomOut(float Value)
{
    InteractMesh->SetCollisionEnabled(OriginCollision);
    SetActorLocationAndRotation(OriginLocation, OriginRotator);
}

void AInteractZoomObjectBase::BeginPlay()
{
    Super::BeginPlay();

    FInputAxisKeyMapping rotateKey("Rotate", EKeys::MouseY, 1.f);
    FInputActionKeyMapping endInteractKey("EndInteract", EKeys::RightMouseButton, 0, 0, 0, 0);

    InputComponent->BindAxis("Rotate", this, &AInteractZoomObjectBase::RotateActor);
    InputComponent->BindAction("EndInteract", IE_Pressed, this, &AInteractZoomObjectBase::UnSelected);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(rotateKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(endInteractKey);

    //FInputAxisKeyMapping forwardKey("Forward", EKeys::W, 1.f);
    //PlayerInputComponent->BindAxis("Forward", this, &AMyCharacter::MoveForward);
    //PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
    //GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(forwardKey);
    //GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(jumpKey);
}

