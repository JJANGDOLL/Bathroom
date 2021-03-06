// Fill out your copyright notice in the Description page of Project Settings.


#include "ToiletBoothDoor.h"
#include "Fastest.h"

AToiletBoothDoor::AToiletBoothDoor()
    : AInteractActObjectBase()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/MMSupermarket/SMBuilding/Mesh/SM_ToiletBooth_Door.SM_ToiletBooth_Door'"));
	if(SM_FE.Succeeded())
	{
		InteractMesh->SetStaticMesh(SM_FE.Object);
		MeshSize = InteractMesh->GetStaticMesh()->GetBoundingBox().GetSize();
		InteractActor->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = InteractMesh->GetCollisionEnabled();
	}
}

void AToiletBoothDoor::OnSelected()
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

void AToiletBoothDoor::SmoothInteract(float Value)
{
	SetActorRotation(FMath::Lerp(OriginRotator, OpenRotator, Value));
}

void AToiletBoothDoor::BeginPlay()
{
    Super::BeginPlay();

	OriginRotator = GetActorRotation();
	OpenRotator = OriginRotator + FRotator(0, 90.f, 0);
}
