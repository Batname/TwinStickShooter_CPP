// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "HeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_CPP_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AHeroCharacter();


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Hero Character")
	class USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, Category = "Hero Character")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Hero Character")
	class UArrowComponent* GunTempComponent;

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

	bool bIsFire = false;
	bool bIsFiring = false;
};
