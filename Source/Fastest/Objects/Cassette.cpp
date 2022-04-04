// Fill out your copyright notice in the Description page of Project Settings.


#include "Cassette.h"

ACassette::ACassette()
	: AInteractZoomObjectBase()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/OldBrickHouse/Meshes/Props/SM_Cassette.SM_Cassette'"));
	if(SM_FE.Succeeded())
	{
		InteractMesh->SetStaticMesh(SM_FE.Object);
		MeshSize = InteractMesh->GetStaticMesh()->GetBoundingBox().GetSize();
		InteractActor->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = InteractMesh->GetCollisionEnabled();
		//FEMesh->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		//MLCGLOG(Display, TEXT("%s"), *temp.GetSize().ToString());
	}
}
