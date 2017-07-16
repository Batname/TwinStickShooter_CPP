// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

AHeroCharacter::AHeroCharacter()
{
	// Add Spring arm camera
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bInheritPitch = 0;
	SpringArmComponent->bInheritRoll = 0;
	SpringArmComponent->bInheritYaw = 0;
	SpringArmComponent->bDoCollisionTest = 0;
	SpringArmComponent->AddRelativeRotation(FRotator(-70.f, 0.f, 0.f));

	// Add Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->AddRelativeLocation(FVector(-300.f, 0.f, 0.f));

	// Set Player to be controller by lowest number player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &AHeroCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AHeroCharacter::RotateCharacter);
	PlayerInputComponent->BindAxis("LookRight", this, &AHeroCharacter::RotateCharacter);
}


void AHeroCharacter::MoveUp(float Value)
{
	AddMovementInput(FVector(1.f, 0.f, 0.f), Value);
}

void AHeroCharacter::MoveRight(float Value)
{
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}

void AHeroCharacter::RotateCharacter(float Value)
{
	// If no controller return
	if (Controller == nullptr)
	{
		return;
	}

	// Store in vectore value
	LookVector = FVector(0.f, Value + LookVector.Y, 0.f);

	// Reset values if more then circle
	if (LookVector.Y > 360 || LookVector.Y < -360)
	{
		LookVector.Y = 0.f;
	}

	// Assign value to rotation
	if (LookVector.Size() > MinLookVectorLenght)
	{
		Controller->SetControlRotation(FRotator(0.f, LookVector.Y, 0.f));
	}
}