// Fill out your copyright notice in the Description page of Project Settings.


#include "Cassette.h"

ACassette::ACassette()
	: AInteractZoomObjectBase()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/OldBrickHouse/Meshes/Props/SM_Cassette.SM_Cassette'"));
	if(SM_FE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_FE.Object);
		MeshSize = Mesh->GetStaticMesh()->GetBoundingBox().GetSize();
		CenterPoint->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = Mesh->GetCollisionEnabled();
		//FEMesh->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		//MLCGLOG(Display, TEXT("%s"), *temp.GetSize().ToString());
	}
}
