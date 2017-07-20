// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "DamagableInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_CPP_API AEnemyCharacter : public ABaseCharacter, public IDamagableInterface
{
	GENERATED_BODY()
	
	
public:
	/** Constructor */
	AEnemyCharacter();

	virtual void BeginPlay() override;
	

private:
	/** Sceletal mesh reference */
	class USkeletalMeshComponent* SkeletalMesh;

	/** Reference to Here character */
	class AHeroCharacter* HeroCharacter = nullptr;

	void DamageTheHero();


	FTimerHandle DamageTimerHandle;

	class ATwinStickShooter_CPPGameModeBase* GameModeBase;

protected:

	/** Implementation of Damage interface */
	virtual void AffectHealth(float Delta) override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* DamageVolume;

	/** Damage overlap function declaration */
	UFUNCTION()
	void OnDamageVolumeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDamageVolumeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly)
	float EnemyDamage = 20.f;

	UPROPERTY(EditDefaultsOnly)
	float AttacksPerSecond = 2.f;
};
