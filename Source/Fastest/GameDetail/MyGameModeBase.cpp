// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Character/MyCharacter.h"
#include "GameDetail/MyHUD.h"
#include "GameDetail/PPZoomVolume.h"
#include "Fastest.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
    HUDClass = AMyHUD::StaticClass();

    PrimaryActorTick.bCanEverTick = true;
}

void AMyGameModeBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    PlayedTime += DeltaSeconds;

    if(bSwitch)
    {
        GetWorldSettings()->LightmassSettings.EnvironmentIntensity = 0;
    }
    else
    {
        GetWorldSettings()->LightmassSettings.EnvironmentIntensity = 1;
    }
}

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    FTransform tempLoc;
    PPVolume = GetWorld()->SpawnActor<APPZoomVolume>(APPZoomVolume::StaticClass(), tempLoc);

    Passwd.Add(FText::FromString("1"));
    Passwd.Add(FText::FromString("2"));
    Passwd.Add(FText::FromString("3"));
    Passwd.Add(FText::FromString("4"));
}

