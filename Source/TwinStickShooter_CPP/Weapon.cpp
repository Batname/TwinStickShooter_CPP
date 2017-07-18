// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Projectile.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ArrowComponent.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Attach a scene componet to root
	USceneComponent * SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;

	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComponent"));
	GunMeshComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_FPGun(TEXT("/Game/FPWeapon/Mesh/SK_FPGun"));
	if (SK_FPGun.Succeeded())
	{
		GunMeshComponent->SetSkeletalMesh(SK_FPGun.Object);
	}

	GunMeshComponent->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(GunMeshComponent);
	ArrowComponent->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	ArrowComponent->SetRelativeLocation(FVector(0.f, 0.f, 10.f));


}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::PullTrigger()
{
	if (!bIsTrigger)
	{
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, TEXT("Fire"));

		GetWorld()->GetTimerManager().SetTimer(SpawnProjectilesTimer, TimerDel, 1.f / RoundsPerSecond, true);
		bIsTrigger = true;
	}
}

void AWeapon::ReleaseTrigger()
{
	if (!bIsTrigger)
	{
		GetWorldTimerManager().ClearTimer(SpawnProjectilesTimer);
	}
}

void AWeapon::Fire()
{

	if (BP_Projectile == nullptr)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	FTransform Transform = ArrowComponent->GetComponentTransform();

	GetWorld()->SpawnActor<AProjectile>(BP_Projectile, Transform.GetLocation(), Transform.Rotator());
}
