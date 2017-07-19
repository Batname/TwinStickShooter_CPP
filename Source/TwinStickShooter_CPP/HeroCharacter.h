// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "DamagableInterface.h"
#include "HeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_CPP_API AHeroCharacter : public ABaseCharacter, public IDamagableInterface
{
	GENERATED_BODY()

public:
	AHeroCharacter();


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Implementation of Damage interface */
	virtual void AffectHealth(float Delta) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Hero Character")
	class USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, Category = "Hero Character")
	class UCameraComponent* CameraComponent;

	/** The projectile to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Hero Character")
	TSubclassOf<class AWeapon> BP_Weapon;

	virtual void BeginPlay() override;

// ------ Movement -------------------
// -----------------------------------
private:
	void MoveUp(float Value);
	void MoveRight(float Value);
	void RotateCharacter(float Value);
	void ToggleFire();

	FVector NewVector = FVector(0.f);
	FVector OldVector = FVector(0.f);

	/** Min lenght of look vector */
	UPROPERTY(EditDefaultsOnly, Category = "Hero Character", meta = (AllowPrivateAccess = "true"))
	float MinLookVectorLenght = 0.25f;

	class AWeapon* Weapon = nullptr;

	/** Toogle space key */
	bool bIsFire = false;
	/** Toogle firing */
	bool bIsFiring = false;

	/** Reference to game mode */
	class ATwinStickShooter_CPPGameModeBase* GameModeBase;

	/** Reference to sceletal mesh */
	class USkeletalMeshComponent* SkeletalMesh;
};
