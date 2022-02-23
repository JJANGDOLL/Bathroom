// Fill out your copyright notice in the Description page of Project Settings.


#include "ToiletPaperRoll.h"

// Sets default values
AToiletPaperRoll::AToiletPaperRoll()
	: AInteractZoomObjectBase()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/MMSupermarket/Props/Mesh/SM_ToiletPaper_Roll.SM_ToiletPaper_Roll'"));
	if(SM_FE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_FE.Object);
		MeshSize = Mesh->GetStaticMesh()->GetBoundingBox().GetSize();
		CenterPoint->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = Mesh->GetCollisionEnabled();
	}
}
