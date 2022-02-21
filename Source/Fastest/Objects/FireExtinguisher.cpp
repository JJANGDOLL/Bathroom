// Fill out your copyright notice in the Description page of Project Settings.

#include "FireExtinguisher.h"

#include "Fastest.h"

#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFireExtinguisher::AFireExtinguisher()
{
	PrimaryActorTick.bCanEverTick = true;

	CeilPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CEIL"));
	RootComponent = CeilPoint;

	CenterPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CENTER"));
	CenterPoint->SetupAttachment(CeilPoint);

	FEMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	FEMesh->SetupAttachment(CenterPoint);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/MMSupermarket/Props/Mesh/SM_FireExtinguisher.SM_FireExtinguisher'"));
	if(SM_FE.Succeeded())
	{
		FEMesh->SetStaticMesh(SM_FE.Object);
		FVector MeshSize = FEMesh->GetStaticMesh()->GetBoundingBox().GetSize();
		CenterPoint->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = FEMesh->GetCollisionEnabled();
		//FEMesh->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		//MLCGLOG(Display, TEXT("%s"), *temp.GetSize().ToString());
	}
}

// Called when the game starts or when spawned
void AFireExtinguisher::BeginPlay()
{
	Super::BeginPlay();
	
	OriginLocation = GetActorLocation();
	OriginRotator = GetActorRotation();
	GetActorBounds(false, Origin, BoxExtend);
}

void AFireExtinguisher::OffFocused()
{
	//MLCGLOG_S(Display);
	FEMesh->SetRenderCustomDepth(false);
}

void AFireExtinguisher::OnFocused()
{
	//MLCGLOG_S(Display);
	FEMesh->SetRenderCustomDepth(true);
}

void AFireExtinguisher::ZoomIn(FVector ScreenCenter)
{
	OffFocused();
	FEMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorLocation(FVector(ScreenCenter.X, ScreenCenter.Y, ScreenCenter.Z));
}

void AFireExtinguisher::ZoomOut()
{
	OnFocused();
	FEMesh->SetCollisionEnabled(OriginCollision);
	SetActorLocationAndRotation(OriginLocation, OriginRotator);
}
