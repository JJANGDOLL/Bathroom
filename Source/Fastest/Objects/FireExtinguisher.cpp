// Fill out your copyright notice in the Description page of Project Settings.

#include "FireExtinguisher.h"

#include "Fastest.h"

#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AFireExtinguisher::AFireExtinguisher()
{

	FEMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = FEMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_FE(TEXT("StaticMesh'/Game/MMSupermarket/Props/Mesh/SM_FireExtinguisher.SM_FireExtinguisher'"));
	if(SM_FE.Succeeded())
	{
		FEMesh->SetStaticMesh(SM_FE.Object);
	}

}

// Called when the game starts or when spawned
void AFireExtinguisher::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFireExtinguisher::OffFocused()
{
	//MLCGLOG_S(Display);
	FEMesh->SetRenderCustomDepth(false);
}

void AFireExtinguisher::OnFocused()
{
	//MLCGLOG_S(Display);
	FEMesh->SetRenderCustomDepth(true);
}

