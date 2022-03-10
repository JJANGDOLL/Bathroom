// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Character/MyCharacter.h"
#include "GameDetail/MyHUD.h"
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
}

