// Fill out your copyright notice in the Description page of Project Settings.


#include "FlourescentRectLight.h"
#include "Components/RectLightComponent.h"

AFlourescentRectLight::AFlourescentRectLight()
{
	LampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LAMP(TEXT("StaticMesh'/Game/SwimmingPool/Meshes/SM_SquareLight.SM_SquareLight'"));
	LampMesh->SetupAttachment(RootComponent);
	if(SM_LAMP.Succeeded())
	{
		LampMesh->SetStaticMesh(SM_LAMP.Object);
		FVector MeshSize = LampMesh->GetStaticMesh()->GetBoundingBox().GetSize();

		URectLightComponent* pLight = CreateDefaultSubobject<URectLightComponent>(TEXT("LIGHT"));
		pLight->SetupAttachment(LampMesh);

		pLight->CastShadows = false;

		pLight->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

		pLight->Intensity = LIGHT_INTENSITY;

		this->Light = Cast<ULocalLightComponent>(pLight);
	}
}
