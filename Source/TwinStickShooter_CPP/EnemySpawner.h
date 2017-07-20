// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TWINSTICKSHOOTER_CPP_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UFUNCTION()
	void SpawnEnemy();

	uint32 GetEnemiesOnScene() { return EnemiesOnScene; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Spawn box volume */
	UPROPERTY(EditDefaultsOnly, Category = EnemySpawner)
	class UBoxComponent* WhereToSpawn;

	/** The enemy to spawn */
	UPROPERTY(EditAnywhere, Category = EnemySpawner)
	TSubclassOf<class AEnemyCharacter> BP_EnemyCharacter;

	UPROPERTY(EditAnywhere, Category = EnemySpawner)
	uint32 MaxEnemyOnScene = 10;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector GetRandomPointInVolume();

	uint32 EnemiesOnScene = 0;
};
