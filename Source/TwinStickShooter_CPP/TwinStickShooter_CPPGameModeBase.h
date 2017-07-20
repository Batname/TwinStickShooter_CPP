// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TwinStickShooter_CPPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_CPP_API ATwinStickShooter_CPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FTransform PlayerSpawnTransform;
	
	/** Holds the logic for re-spawning player if he die */
	UFUNCTION()
	void RespawnPlayer();

	UFUNCTION()
	void IncrementScore();

	UFUNCTION()
	int GetScore() { return Score; }

	UFUNCTION()
	void SetScoreZero() { Score = 0; }

	class AEnemySpawner* GetEnemySpawner() { return EnemySpawner; }

protected:
	/** Reference to Player Character blueprint */
	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	TSubclassOf<class AHeroCharacter> BP_HeroCharacter;


	virtual void BeginPlay() override;

	float EnemiesPerSecond = 2.f;

	/*Property which is pointing to our Widget Blueprint in order to instantiate it using c++*/
	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	TSubclassOf<class UTwinSkickWidget> BP_TwinSkickWidget;


	/** Reference to Player Character blueprint */
	UPROPERTY(VisibleAnywhere, Category = "GameMode")
	int Score = 0;

	/** Reference to Player Character blueprint */
	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	int DeltaScore = 500;

private:
	/** Reference to spawn volume actor */
	UPROPERTY()
	class AEnemySpawner* EnemySpawner;
};
