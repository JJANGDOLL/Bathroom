// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Character/MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
}
