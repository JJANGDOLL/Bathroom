// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Fastest.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/Interactable.h"
#include "Kismet/KismetMathLibrary.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 80.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 
}

void AMyCharacter::AddControllerPitchInput(float Val)
{
	if(!bZoom)
		Super::AddControllerPitchInput(Val);
	else
	{
		FocusedActor->AddActorLocalRotation(FQuat(FRotator(Val, 0, 0)));
	}
}

void AMyCharacter::AddControllerYawInput(float Val)
{
	if(!bZoom)
		Super::AddControllerYawInput(Val);
	else
	{
		FocusedActor->AddActorLocalRotation(FQuat(FRotator(0, Val, 0)));
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

	PlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bZoom)
	{
		FHitResult hitResult;

		// CheckLineTrace
		FVector worldLoc;
		FVector worldDir;
		PlayerController->DeprojectScreenPositionToWorld(ViewportCenter.X, ViewportCenter.Y, worldLoc, worldDir);

		bool bHitRet = GetWorld()->LineTraceSingleByChannel(hitResult, \
			worldLoc, \
			worldLoc + worldDir * 300, \
			ECollisionChannel::ECC_Visibility);


		if(!FocusedActor)
		{
			if(bHitRet)
			{
				AActor* hittedActor = hitResult.GetActor();
				UClass* ActorClass = hittedActor->GetClass();

				if(ActorClass->ImplementsInterface(UInteractable::StaticClass()))
				{
					FocusedActor = hittedActor;
					IInteractable* interactObject = Cast<IInteractable>(FocusedActor);
					interactObject->OnFocused();
				}

#ifdef __DEV_DEBUG__
				if(bDebug)
				{
					MLCGLOG(Display, TEXT("%s"), *hitResult.GetActor()->GetName());
				}
#endif
			}
			else
			{

			}

		}
		else if(!!FocusedActor)
		{
			if(bHitRet)
			{
				AActor* hittedActor = hitResult.GetActor();
				UClass* ActorClass = hittedActor->GetClass();

				if(ActorClass->ImplementsInterface(UInteractable::StaticClass()))
				{
					if(FocusedActor != hittedActor)
					{
						IInteractable* interactObject;
						interactObject = Cast<IInteractable>(FocusedActor);
						interactObject->OffFocused();

						FocusedActor = hitResult.GetActor();
						interactObject = Cast<IInteractable>(FocusedActor);
						interactObject->OnFocused();
					}
				}
				else
				{
					ActorClass = FocusedActor->GetClass();

					if(ActorClass->ImplementsInterface(UInteractable::StaticClass()))
					{
						IInteractable* interactObject = Cast<IInteractable>(FocusedActor);
						interactObject->OffFocused();
					}
					FocusedActor = NULL;
				}
			}
			else
			{
				UClass* ActorClass = FocusedActor->GetClass();

				if(ActorClass->ImplementsInterface(UInteractable::StaticClass()))
				{
					IInteractable* interactObject = Cast<IInteractable>(FocusedActor);
					interactObject->OffFocused();
				}
				FocusedActor = NULL;

#ifdef __DEV_DEBUG__
				if(bDebug)
				{
					MLCGLOG(Display, TEXT("None"));
				}
#endif
			}

		}
#ifdef __DEV_DEBUG__
		DrawDebugLine(GetWorld(), worldLoc, worldLoc + worldDir * 300, FColor::Red, false, 0.5f, 10.f);
#endif
	}

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	FInputAxisKeyMapping forwardKey("Forward", EKeys::W, 1.f);
	FInputAxisKeyMapping backKey("Back", EKeys::S, -1.f);
	FInputAxisKeyMapping rightKey("Right", EKeys::D, 1.f);
	FInputAxisKeyMapping leftKey("Left", EKeys::A, -1.f);
	FInputAxisKeyMapping lookupKey("LookUp", EKeys::MouseY, -1.f);
	FInputAxisKeyMapping turnKey("Turn", EKeys::MouseX, 1.f);

	FInputActionKeyMapping jumpKey("Jump", EKeys::SpaceBar, 0, 0, 0, 0);
	FInputActionKeyMapping lClickKey("LClick", EKeys::LeftMouseButton, 0, 0, 0, 0);
	FInputActionKeyMapping rClickKey("RClick", EKeys::RightMouseButton, 0, 0, 0, 0);
	FInputActionKeyMapping resetKey("Reset", EKeys::R, 0, 0, 0, 0);

	PlayerInputComponent->BindAxis("Forward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Back", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AMyCharacter::MoveLeft);
	PlayerInputComponent->BindAxis("Left", this, &AMyCharacter::MoveLeft);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
	PlayerInputComponent->BindAction("LClick", IE_Pressed, this, &AMyCharacter::FocusedActorClick);
	PlayerInputComponent->BindAction("RClick", IE_Pressed, this, &AMyCharacter::UnfocusedActorClick);
	PlayerInputComponent->BindAction("Reset", IE_Pressed, this, &AMyCharacter::ResetFocusedActorRot);

	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(forwardKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(backKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(rightKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(leftKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(lookupKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(turnKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(jumpKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(lClickKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(rClickKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(resetKey);
}

void AMyCharacter::MoveForward(float Value)
{
	if((Controller != NULL) && (Value != 0.0f) && (!bZoom))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::MoveLeft(float Value)
{
	if((Controller != NULL) && (Value != 0.0f) && (!bZoom))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::FocusedActorClick()
{
	if(!::IsValid(FocusedActor)) return;
#ifdef __DEV_DEBUG__
    MLCGLOG(Display, TEXT("%s"), *FocusedActor->GetName());
#endif


	FRotator newRot = UKismetMathLibrary::FindLookAtRotation(FocusedActor->GetActorLocation(), GetActorLocation());

	// CheckLineTrace
	FVector worldLoc;
	FVector worldDir;
	PlayerController->DeprojectScreenPositionToWorld(ViewportCenter.X, ViewportCenter.Y, worldLoc, worldDir);

	IInteractable* interactObject = Cast<IInteractable>(FocusedActor);

	interactObject->ZoomIn(worldLoc + worldDir * 100);
	bZoom = true;
}

void AMyCharacter::UnfocusedActorClick()
{
	if(!bZoom) return;

	IInteractable* interactObject = Cast<IInteractable>(FocusedActor);

	interactObject->ZoomOut();
	bZoom = false;
}

void AMyCharacter::ResetFocusedActorRot()
{
	if(!bZoom) return;

	FocusedActor->SetActorRotation(FQuat(FRotator(0, 0, 0)));
}

