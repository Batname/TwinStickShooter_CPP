// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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




