// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "HeroCharacter.h"
#include "TwinStickShooter_CPPGameModeBase.h"


#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyCharacter::AEnemyCharacter()
{
	// Set reference to skeletal mesh
	SkeletalMesh = GetMesh();

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	// Create damage volume and assign to root component
	DamageVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageVolume"));
	DamageVolume->SetupAttachment(RootComponent);
	DamageVolume->bGenerateOverlapEvents = true;
	DamageVolume->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	DamageVolume->SetRelativeLocation(FVector(80.f, 0.f, -65.f));
	DamageVolume->SetRelativeScale3D(FVector(1.f, 1.f, 0.5f));

	// Set as spawned in world
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set material dynamic color
	if (SkeletalMesh != nullptr)
	{
		UMaterialInstanceDynamic* DynamicMatInstance = SkeletalMesh->CreateDynamicMaterialInstance(0);
		if (DynamicMatInstance != nullptr)
		{
			DynamicMatInstance->SetVectorParameterValue(FName("BodyColor"), FLinearColor(0.995f, 0.019f, 0.048f, 1.f));
		}
	}


	DamageVolume->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnDamageVolumeBeginOverlap);
	DamageVolume->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnDamageVolumeEndOverlap);

	GameModeBase = Cast<ATwinStickShooter_CPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AEnemyCharacter::AffectHealth(float Delta)
{
	CalculateHealth(Delta);

	if (bIsDead && !bIsDeadRestarting)
	{
		// Disable collision
		UCapsuleComponent* CapsuleComponent = GetCapsuleComponent();
		CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
		CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		// Detach controller
		DetachFromControllerPendingDestroy();

		// Increment score
		if (GameModeBase != nullptr)
		{
			GameModeBase->IncrementScore();
		}

		// Die after delay
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDel;

		TimerDel.BindLambda([&]
		{
			Destroy();
		});

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 3.f, false);

		bIsDeadRestarting = true;
	}
}

void AEnemyCharacter::OnDamageVolumeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HeroCharacter = Cast<AHeroCharacter>(OtherActor);
	if (HeroCharacter != nullptr)
	{
		GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &AEnemyCharacter::DamageTheHero, (1.f / AttacksPerSecond), true);
	}
}

void AEnemyCharacter::OnDamageVolumeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HeroCharacter == OtherActor)
	{
		GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	}
}

void AEnemyCharacter::DamageTheHero()
{
	if (HeroCharacter != nullptr)
	{
		HeroCharacter->AffectHealth(-EnemyDamage);
	}
}