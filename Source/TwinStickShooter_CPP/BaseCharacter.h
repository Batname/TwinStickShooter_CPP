// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Blueprintable)
class TWINSTICKSHOOTER_CPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Health property */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Base Character")
	float Health = 100;

	/** Death property */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Base Character")
	bool bIsDead = false;

	/** Calculate death function */
	UFUNCTION()
	virtual void CalculateDeath();

	/** Calculate health */
	UFUNCTION(BlueprintCallable, Category = "Base Character")
	virtual void CalculateHealth(float Delta);

#if WITH_EDITOR
	/** Change properties */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	/** Get state of dead restarting */
	UFUNCTION(BlueprintCallable, Category = "Base Character")
	bool IsDeadRestarting() { return bIsDeadRestarting; }

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsDeadRestarting = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
