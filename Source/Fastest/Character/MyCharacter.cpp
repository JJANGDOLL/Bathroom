// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyCharacter::MoveForward(float Value)
{
	if((Controller != NULL) && (Value != 0.0f))
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
	if((Controller != NULL) && (Value != 0.0f))
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

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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


	PlayerInputComponent->BindAxis("Forward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Back", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AMyCharacter::MoveLeft);
	PlayerInputComponent->BindAxis("Left", this, &AMyCharacter::MoveLeft);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);

	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(forwardKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(backKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(rightKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(leftKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(lookupKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(turnKey);
	GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(jumpKey);
}
