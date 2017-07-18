// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "HeroCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

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
}

void AEnemyCharacter::AffectHealth(float Delta)
{
	CalculateHealth(Delta);

	if (bIsDead)
	{
		Destroy();
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
	HeroCharacter->AffectHealth(-Damage);
}