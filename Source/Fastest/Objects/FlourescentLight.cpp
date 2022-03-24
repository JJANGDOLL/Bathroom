// Fill out your copyright notice in the Description page of Project Settings.


#include "FlourescentLight.h"
#include "Components/PointLightComponent.h"

AFlourescentLight::AFlourescentLight()
	: AWorldLightBase()
{
	LampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_LAMP(TEXT("StaticMesh'/Game/SwimmingPool/Meshes/SM_LongLight.SM_LongLight'"));
	LampMesh->SetupAttachment(RootComponent);
	if(SM_LAMP.Succeeded())
	{
		LampMesh->SetStaticMesh(SM_LAMP.Object);
		FVector MeshSize = LampMesh->GetStaticMesh()->GetBoundingBox().GetSize();

		UPointLightComponent* pLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
		pLight->SetupAttachment(LampMesh);
		pLight->SetSourceRadius(10.f);
		pLight->SetSourceLength(178.5f);
		pLight->CastShadows = false;
		pLight->SetLightColor(FLinearColor(FVector(1.f, 0.86f, 0.65f)));

		pLight->SetRelativeLocation(FVector(0.f, 0.f, 2.f));
		pLight->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
		
		pLight->Intensity = LIGHT_INTENSITY;

		this->Light = Cast<ULocalLightComponent>(pLight);
	}
}
