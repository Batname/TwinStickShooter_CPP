// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnim.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_CPP_API UCharacterAnim : public UAnimInstance
{
	GENERATED_BODY()

protected:
	/** Holds the current speed of our character */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	/** Holds the current velocity rotaiton of our character */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator VelocityRotation;

	/** Holds the current pawn control rotation of our character */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator ControlRotation;

	/** Holds the current pawn control rotation of our character */
	UPROPERTY(BlueprintReadOnly)
	bool bIsDead = false;

	/** Number of dead animation from 0 up to 2*/
	UPROPERTY(BlueprintReadOnly)
	int32 DeadAnimNum = 0;

	/** Holds the current pawn delta yaw */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Direction;

	/** Updates the above parameters */
	UFUNCTION(BlueprintCallable, Category = UpdateAnimationProperties)
	void UpdateAnimationProperties();

private:
	bool bIsDeadAnimStart = false;
};
