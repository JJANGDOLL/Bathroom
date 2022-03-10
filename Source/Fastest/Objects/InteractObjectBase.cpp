// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObjectBase.h"
#include "Fastest.h"

//CurveFloat'/Game/Timeline/TL_Zoom.TL_Zoom'

// Sets default values
AInteractObjectBase::AInteractObjectBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CeilPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CEIL"));
	RootComponent = CeilPoint;

	CenterPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CENTER"));
	CenterPoint->SetupAttachment(CeilPoint);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(CenterPoint);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/MMSupermarket/Props/Mesh/SM_ToiletPaper_Roll.SM_ToiletPaper_Roll'"));
	if(SM_FE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_FE.Object);
		MeshSize = Mesh->GetStaticMesh()->GetBoundingBox().GetSize();
		CenterPoint->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = Mesh->GetCollisionEnabled();
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

// Called when the game starts or when spawned
void AInteractObjectBase::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetActorLocation();
	OriginRotator = GetActorRotation();
	GetActorBounds(false, Origin, BoxExtend);

	if(SmoothCurve)
	{
		MLCGLOG_S(Display);
		FOnTimelineFloat interactCallback;

		interactCallback.BindUFunction(this, FName("SmoothInteract"));
		SmoothTimeline.AddInterpFloat(SmoothCurve, interactCallback);
	}
}


void AInteractObjectBase::OffFocused()
{
	Mesh->SetRenderCustomDepth(false);
}

void AInteractObjectBase::OnFocused()
{
	Mesh->SetRenderCustomDepth(true);
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

