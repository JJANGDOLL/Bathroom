// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Enums/FastestTypes.h"
#include "Components/TimelineComponent.h"
#include "InteractObjectBase.generated.h"

UCLASS()
class FASTEST_API AInteractObjectBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractObjectBase();

	UPROPERTY(VisibleInstanceOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleInstanceOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	class USceneComponent* CeilPoint;

	UPROPERTY(VisibleInstanceOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	class USceneComponent* CenterPoint;

	FVector OriginLocation;
	FRotator OriginRotator;
	FVector Origin;
	FVector BoxExtend;
	FVector MeshSize;

	ECollisionEnabled::Type OriginCollision;
	EObjectInteract::Type InteractType = EObjectInteract::NONE;

	UFUNCTION()
	virtual void SmoothInteract(float Value);

	UCurveFloat* SmoothCurve;
	FTimeline SmoothTimeline;
	float SmoothTimelineLength;

	bool bSwitch = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OffFocused() override;
	virtual void OnFocused() override;
	virtual void OnSelected() override;
	virtual void UnSelected() override;
	virtual EObjectInteract::Type GetInteractObjectType() override;

	virtual void Tick(float DeltaSeconds) override;

};
