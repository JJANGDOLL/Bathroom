// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Utils/MyUtils.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//CHelpers::CreateComponent(this, &NameWidget, "NameWidget", GetMesh());

	Helpers::CreateComponent(this, &TestScene, "TEST");
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	Helpers::GetActEngine();
}


