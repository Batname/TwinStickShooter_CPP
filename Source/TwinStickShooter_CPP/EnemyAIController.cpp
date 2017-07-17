// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Kismet/GameplayStatics.h"

#include "HeroCharacter.h"


AEnemyAIController::AEnemyAIController()
{
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	// Set a tracking timer
	{
		FTimerHandle TimerHandle;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyAIController::TrackPlayer, 1.f, true);
	}
}

void AEnemyAIController::TrackPlayer()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController != nullptr)
	{
		MoveToActor(PlayerController->GetPawn(), 5.f, true);
	}
}