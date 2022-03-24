// Fill out your copyright notice in the Description page of Project Settings.


#include "ToiletBoothDoor2.h"
#include "Fastest.h"

AToiletBoothDoor2::AToiletBoothDoor2()
	: AInteractActObjectBase()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/SwimmingPool/Meshes/SM_CubicleDoor.SM_CubicleDoor'"));
	if(SM_FE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_FE.Object);
		MeshSize = Mesh->GetStaticMesh()->GetBoundingBox().GetSize();
		CenterPoint->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = Mesh->GetCollisionEnabled();
	}
}

void AToiletBoothDoor2::OnSelected()
{
	MLCGLOG_S(Display);
	if(bOpened)
	{
		bOpened = false;
		SmoothTimeline.Reverse();
	}
	else
	{
		bOpened = true;
		SmoothTimeline.PlayFromStart();
	}
}

void AToiletBoothDoor2::SmoothInteract(float Value)
{
	SetActorRotation(FMath::Lerp(OriginRotator, OpenRotator, Value));
}

void AToiletBoothDoor2::BeginPlay()
{
	Super::BeginPlay();

	OriginRotator = GetActorRotation();
	OpenRotator = OriginRotator + FRotator(0, 90.f, 0);
}
