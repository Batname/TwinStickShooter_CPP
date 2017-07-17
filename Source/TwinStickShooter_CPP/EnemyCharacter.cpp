// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	// Set reference to skeletal mesh
	SkeletalMesh = GetMesh();

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set material dynamic color
	if (SkeletalMesh != nullptr)
	{
		UMaterialInstanceDynamic* DynamicMatInstance = SkeletalMesh->CreateDynamicMaterialInstance(0);
		if (DynamicMatInstance != nullptr)
		{
			DynamicMatInstance->SetVectorParameterValue(FName("BodyColor"), FLinearColor(0.995f, 0.019f, 0.048f, 1.f));
		}
	}
}