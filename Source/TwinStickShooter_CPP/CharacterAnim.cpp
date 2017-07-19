// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnim.h"

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

	}
}