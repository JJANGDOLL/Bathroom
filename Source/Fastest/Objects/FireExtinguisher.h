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

	UPROPERTY(VisibleInstanceOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	class USceneComponent* CeilPoint;

	UPROPERTY(VisibleInstanceOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	class USceneComponent* CenterPoint;

	FVector OriginLocation;
	FRotator OriginRotator;
	FVector Origin;
	FVector BoxExtend;

	ECollisionEnabled::Type OriginCollision;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// IInteractable Interface
	virtual void OffFocused() override;
	virtual void OnFocused() override;
	virtual void ZoomIn(FVector ScreenCenter) override;
	virtual void ZoomOut() override;
};
