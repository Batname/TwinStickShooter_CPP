// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TWINSTICKSHOOTER_CPP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* GunMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* ArrowComponent;

	/** The projectile to spawn */
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class AProjectile> BP_Projectile;

	UFUNCTION()
	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float RoundsPerSecond = 5.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void PullTrigger();

	UFUNCTION()
	void ReleaseTrigger();

	UFUNCTION()
	class USkeletalMeshComponent* GetGunMeshComponent() { return GunMeshComponent; }

private:
	FTimerHandle SpawnProjectilesTimer;
	
	bool bIsTrigger = false;
};
