// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class FASTEST_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(EditInstanceOnly, Category = Debug)
	bool bDebug = false;

	UPROPERTY(VisibleInstanceOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleInstanceOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	APlayerController* PlayerController;

	FORCEINLINE FVector2D GetViewportCenter() { return ViewportCenter; };

	FVector2D ViewportSize;
	FVector2D ViewportCenter;

	bool bZoom = false;

	virtual void AddControllerPitchInput(float Val) override;
	virtual void AddControllerYawInput(float Val) override;

	UFUNCTION()
	void SetCrouch(float Value);

	UCurveFloat* CrouchCurve;
	FTimeline CrouchTimeline;
	float CourchTimelineLength;
	bool bCrouched = false; 

	class APlayerCameraManager* CameraManager;

	virtual void PossessedBy(AController* NewController) override;

protected:
	void MoveForward(float Value);
	void MoveLeft(float Value);
	void ToggleCrouch();

	void FocusedActorClick();
	void UnfocusedActorClick();
	void ResetFocusedActorRot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	AActor* FocusedActor;

};
