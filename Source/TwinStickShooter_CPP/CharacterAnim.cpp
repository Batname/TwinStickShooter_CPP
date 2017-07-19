// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnim.h"
#include "BaseCharacter.h"

void UCharacterAnim::UpdateAnimationProperties()
{
	APawn* Pawn = TryGetPawnOwner();

	if (Pawn != nullptr)
	{
		FVector Velocity = Pawn->GetVelocity();

		Speed = Velocity.Size();
		VelocityRotation = Velocity.Rotation();

		AController* Controller = Pawn->GetController();
		if (Controller != nullptr)
		{
			ControlRotation = Controller->GetControlRotation();
			Direction = (VelocityRotation - ControlRotation).Yaw;
		}

		// Try to cast our player
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Pawn);
		if (BaseCharacter != nullptr)
		{
			bIsDead = BaseCharacter->bIsDead;

			if (bIsDead && !bIsDeadAnimStart)
			{
				DeadAnimNum = FMath::FRandRange(0, 2);
				bIsDeadAnimStart = true;
			}
		}
	}
}