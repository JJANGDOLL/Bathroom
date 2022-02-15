// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "FireExtinguisher.generated.h"

UCLASS()
class FASTEST_API AFireExtinguisher : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireExtinguisher();

	UPROPERTY(VisibleInstanceOnly, Category=Mesh, Meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* FEMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OffFocused() override;
	virtual void OnFocused() override;
};
