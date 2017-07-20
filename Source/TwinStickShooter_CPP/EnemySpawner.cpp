// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "EnemyCharacter.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create root box component
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
	WhereToSpawn->SetCollisionProfileName(FName("OverlapAll"));
	WhereToSpawn->SetSimulatePhysics(false);
	WhereToSpawn->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// increase enemies on scene
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDel;

		TimerDel.BindLambda([&]
		{
			MaxEnemyOnScene++;
		});

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, FMath::FRandRange(5.f, 10.f), true);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	// Check limit of enemies
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundActors);
	EnemiesOnScene = FoundActors.Num();

	if (EnemiesOnScene >= MaxEnemyOnScene)
	{
		return;
	}

	// Get character reference
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (BP_EnemyCharacter == nullptr || Character == nullptr)
	{
		return;
	}

	FVector SpawnLocation = GetRandomPointInVolume();
	FVector CharacterLocation = Character->GetActorLocation();

	// Rotate to character
	FRotator SpawnRotation;
	SpawnRotation.Yaw = (CharacterLocation - SpawnLocation).Rotation().Yaw;
	SpawnRotation.Pitch = 0.f;
	SpawnRotation.Roll = 0.f;

	// Spawn parameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	// Spawn an Enemy
	ACharacter* EnemyCharacter = GetWorld()->SpawnActor<AEnemyCharacter>(BP_EnemyCharacter, SpawnLocation, SpawnRotation, SpawnParams);
}

FVector AEnemySpawner::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtend = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtend);
}