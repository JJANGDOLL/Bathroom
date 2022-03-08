// Fill out your copyright notice in the Description page of Project Settings.


#include "LampSwitch.h"
#include "Fastest.h"
#include "CeillingLamp.h"
#include "Interfaces/Switch.h"

ALampSwitch::ALampSwitch()
    : AInteractActObjectBase()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/Meshes/SM_Switch.SM_Switch'"));
	if(SM_FE.Succeeded())
	{
		Mesh->SetStaticMesh(SM_FE.Object);
		MeshSize = Mesh->GetStaticMesh()->GetBoundingBox().GetSize();
		CenterPoint->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = Mesh->GetCollisionEnabled();
	}
}

void ALampSwitch::OnSelected()
{
	MLCGLOG_S(Display);
	for(ACeillingLamp* lamp : Lamps)
	{
		ISwitch* swt = Cast<ISwitch>(lamp);

		if(swt != nullptr)
		{
			if(bOn)
			{
				swt->Off();
			}
			else
			{
				swt->On();
			}
		}
	}
	bOn = !bOn;
}

