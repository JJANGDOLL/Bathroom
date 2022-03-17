// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FASTEST_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameModeBase();

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE float GetPlayedTime() { return PlayedTime; }

	class APPZoomVolume* PPVolume;
	class APPZoomVolume* GetPostProcess() { return PPVolume; }

private:
	float PlayedTime = 0.f;

protected:
	virtual void BeginPlay() override;

};
