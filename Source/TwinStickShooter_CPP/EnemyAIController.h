// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_CPP_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	/** Constructor */
	AEnemyAIController();

	/** Blackboard key */
	UPROPERTY(EditDefaultsOnly, Category = EnemyAI)
	FName BlackboardKey = "Player";

	/** Executes right when the controlles posssess a Pawn */
	virtual void Possess(APawn* Pawn) override;

	virtual void BeginPlay() override;

	/** Keep track Player */
	UFUNCTION()
	void TrackPlayer();

private:
	/** Behavior tree ref */
	class UBehaviorTreeComponent* BehaviorComp;

	/** Blackboard reference */
	class UBlackboardComponent* BlackboardComp;
};
