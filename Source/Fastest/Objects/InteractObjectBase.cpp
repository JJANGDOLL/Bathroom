// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObjectBase.h"
#include "Fastest.h"
#include "Components/BillboardComponent.h"

AInteractObjectBase::AInteractObjectBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetSprite(nullptr);
	RootComponent = Billboard;

	InteractPivot = CreateDefaultSubobject<UBillboardComponent>(TEXT("InteractPivot"));
	InteractPivot->SetSprite(nullptr);
	InteractPivot->SetupAttachment(RootComponent);

	InteractActor = CreateDefaultSubobject<USceneComponent>(TEXT("InteractActor"));
	InteractActor->SetupAttachment(RootComponent);
	InteractActor->SetHiddenInGame(true);

	InteractMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractMesh"));
	InteractMesh->SetupAttachment(InteractActor);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/MMSupermarket/Props/Mesh/SM_ToiletPaper_Roll.SM_ToiletPaper_Roll'"));
	if(SM_FE.Succeeded())
	{
		InteractMesh->SetStaticMesh(SM_FE.Object);
		OriginCollision = InteractMesh->GetCollisionEnabled();
	}

	static ConstructorHelpers::FObjectFinder<UCurveFloat> CF_ZOOM(TEXT("CurveFloat'/Game/Timeline/TL_Zoom.TL_Zoom'"));
	if(CF_ZOOM.Succeeded())
	{
		SmoothCurve = CF_ZOOM.Object;
	}
}

void AInteractObjectBase::SmoothInteract(float Value)
{
	MLCGLOG_S(Display);
}

void AInteractObjectBase::ZoomFinished()
{

}

// Called when the game starts or when spawned
void AInteractObjectBase::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetActorLocation();
	OriginRotator = GetActorRotation();
	GetActorBounds(false, Origin, BoxExtend);

	FOnTimelineEventStatic onTimelineFinishedCallback;

	if(SmoothCurve)
	{
		MLCGLOG_S(Display);
		FOnTimelineFloat interactCallback;

		interactCallback.BindUFunction(this, FName("SmoothInteract"));
		SmoothTimeline.AddInterpFloat(SmoothCurve, interactCallback);

		SmoothTimeline.SetPropertySetObject(this);
		SmoothTimeline.SetDirectionPropertyName(FName("AnimDir"));

		onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("ZoomFinished")));
		SmoothTimeline.SetTimelineFinishedFunc(onTimelineFinishedCallback);
	}
}


void AInteractObjectBase::OffFocused()
{
	InteractMesh->SetRenderCustomDepth(false);
}

void AInteractObjectBase::OnFocused()
{
	InteractMesh->SetRenderCustomDepth(true);
}

//void AInteractObjectBase::ZoomIn(FVector ScreenCenter)
//{
//	OffFocused();
//	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//	SetActorLocation(FVector(ScreenCenter.X, ScreenCenter.Y, ScreenCenter.Z));
//}
//
//void AInteractObjectBase::ZoomOut()
//{
//	OnFocused();
//	Mesh->SetCollisionEnabled(OriginCollision);
//	SetActorLocationAndRotation(OriginLocation, OriginRotator);
//}

void AInteractObjectBase::OnSelected()
{
	MLCGLOG_S(Warning);

	
}

void AInteractObjectBase::UnSelected()
{
	MLCGLOG_S(Warning);
}

EObjectInteract::Type AInteractObjectBase::GetInteractObjectType()
{
	return InteractType;
}

void AInteractObjectBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	SmoothTimeline.TickTimeline(DeltaSeconds);
}

