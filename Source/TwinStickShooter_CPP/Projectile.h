// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TWINSTICKSHOOTER_CPP_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Collision sphere */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	class USphereComponent* ProjectileCollision;


	/** Mesh sphere */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	class UStaticMeshComponent* LaserMeshComp;

	/** Projectile movement component */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	float Damage = 20.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
