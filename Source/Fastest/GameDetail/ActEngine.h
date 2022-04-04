// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActEngine.generated.h"

UCLASS()
class FASTEST_API AActEngine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActEngine();

	UPROPERTY(VisibleInstanceOnly)
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleInstanceOnly)
	class USceneComponent* InteractLocation;

	UPROPERTY(VisibleInstanceOnly)
	class USceneComponent* TakeLocation;
};
