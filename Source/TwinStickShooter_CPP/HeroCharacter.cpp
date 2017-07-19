// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Weapon.h"
#include "TwinStickShooter_CPPGameModeBase.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

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

	// add actor tag
	Tags.Add(FName("Friendly"));

	SkeletalMesh = GetMesh();
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Setup weapon
	if (BP_Weapon != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		if (SkeletalMesh != nullptr)
		{
			FTransform Transform = SkeletalMesh->GetComponentTransform();
			Weapon = GetWorld()->SpawnActor<AWeapon>(BP_Weapon, Transform.GetLocation(), Transform.Rotator(), SpawnParams);
			
			FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
			Weapon->AttachToComponent(SkeletalMesh, TransformRules, FName("GunSocket"));
		}

		// USkeletalMeshComponent* WeaponSkeletalMesh = Weapon->GetGunMeshComponent();
	}

	// Set PlayerSpawnTransform in GameMode
	GameModeBase = Cast<ATwinStickShooter_CPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeBase != nullptr)
	{
		GameModeBase->PlayerSpawnTransform = GetTransform();
	}
}


void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &AHeroCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AHeroCharacter::RotateCharacter);
	PlayerInputComponent->BindAxis("LookRight", this, &AHeroCharacter::RotateCharacter);

	PlayerInputComponent->BindAction("ToggleFire", IE_Pressed, this, &AHeroCharacter::ToggleFire);
}

void AHeroCharacter::ToggleFire()
{
	if (!bIsFire)
	{
		bIsFire = true;
	}
	else
	{
		bIsFire = false;
	}
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
	NewVector = FVector(0.f, 3.f * Value + OldVector.Y, 0.f);

	// Reset values if more then circle
	if (NewVector.Y > 360 || NewVector.Y < -360)
	{
		NewVector.Y = 0.f;
	} 

	// Assign value to rotation
	if ((NewVector - OldVector).Size() > MinLookVectorLenght)
	{
		Controller->SetControlRotation(FRotator(0.f, NewVector.Y, 0.f));
	}

	// Toggle wepon logic
	if (Weapon != nullptr)
	{
		if (bIsFire)
		{
			if (!bIsFiring)
			{
				Weapon->PullTrigger();
				bIsFiring = true;
			}
		}
		else
		{
			Weapon->ReleaseTrigger();
			bIsFiring = false;
		}
	}

	OldVector = NewVector;
}

void AHeroCharacter::AffectHealth(float Delta)
{
	CalculateHealth(Delta);

	if (bIsDead && !bIsDeadRestarting)
	{
		// Disable input
		DisableInput(GetWorld()->GetFirstPlayerController());

		// Die after delay
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDel;

		TimerDel.BindLambda([&]
		{
			Destroy();
			if (Weapon != nullptr)
			{
				Weapon->Destroy();
			}

			GameModeBase->RespawnPlayer();
		});
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 3.f, false);

		bIsDeadRestarting = true;
	}

	// TODO just for test
	if (GEngine)
	{
	     GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Red, FString("Player Health: ") + FString::SanitizeFloat(Health));  
	}
}