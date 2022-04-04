// Fill out your copyright notice in the Description page of Project Settings.


#include "LampSwitch.h"
#include "Fastest.h"
#include "Objects/WorldLightBase.h"
#include "Interfaces/Switch.h"

ALampSwitch::ALampSwitch()
    : AInteractActObjectBase()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/Meshes/SM_Switch.SM_Switch'"));
	if(SM_FE.Succeeded())
	{
		InteractMesh->SetStaticMesh(SM_FE.Object);
		MeshSize = InteractMesh->GetStaticMesh()->GetBoundingBox().GetSize();
		InteractActor->SetRelativeLocation(FVector(0, 0, -(MeshSize.Z / 2)));
		OriginCollision = InteractMesh->GetCollisionEnabled();
	}
}

void ALampSwitch::OnSelected()
{
	MLCGLOG_S(Display);
	for(AWorldLightBase* lamp : Lamps)
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

