// Fill out your copyright notice in the Description page of Project Settings.


#include "ToiletBoothDoor.h"

AToiletBoothDoor::AToiletBoothDoor()
    : AInteractObjectBase()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/MMSupermarket/SMBuilding/Mesh/SM_ToiletBooth_Door.SM_ToiletBooth_Door'"));
	if(SM_FE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_FE.Object);
		MeshSize = Mesh->GetStaticMesh()->GetBoundingBox().GetSize();
		CenterPoint->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = Mesh->GetCollisionEnabled();
	}
}
