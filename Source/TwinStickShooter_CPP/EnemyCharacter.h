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

protected:

	virtual void AffectHealth(float Delta) override;
};
