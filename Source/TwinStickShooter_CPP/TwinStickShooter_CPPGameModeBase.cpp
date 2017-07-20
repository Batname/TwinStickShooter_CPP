// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinStickShooter_CPPGameModeBase.h"
#include "HeroCharacter.h"
#include "EnemySpawner.h"
#include "EnemyCharacter.h"
#include "TwinSkickWidget.h"

#include "Kismet/GameplayStatics.h"

void ATwinStickShooter_CPPGameModeBase::RespawnPlayer()
{
	// Destroy enemies
	TArray<AActor*> FoundEnemyActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundEnemyActors);
	for (auto Actor : FoundEnemyActors)
	{
		Actor->Destroy();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	AHeroCharacter* HeroCharacter = GetWorld()->SpawnActor<AHeroCharacter>(BP_HeroCharacter, PlayerSpawnTransform.GetLocation(), PlayerSpawnTransform.Rotator(), SpawnParams);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController != nullptr)
	{
		PlayerController->Possess(HeroCharacter);
	}

	// Set score zero
	SetScoreZero();
}

void ATwinStickShooter_CPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;

	// TODO Only for one Enemy spawner
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		EnemySpawner = Cast<AEnemySpawner>(Actor);
	}

	if (EnemySpawner != nullptr)
	{
		FTimerHandle TimerHandle;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, EnemySpawner, &AEnemySpawner::SpawnEnemy, (1.f / EnemiesPerSecond), true);
	}

	// Crteate user widget
	if (BP_TwinSkickWidget != nullptr)
	{
		UTwinSkickWidget* TwinSkickWidget = CreateWidget<UTwinSkickWidget>(GetWorld(), BP_TwinSkickWidget);
		TwinSkickWidget->AddToViewport();
	}
}

void ATwinStickShooter_CPPGameModeBase::IncrementScore()
{
	Score += DeltaScore;
}