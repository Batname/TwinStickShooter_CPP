// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinStickShooter_CPPGameModeBase.h"
#include "HeroCharacter.h"

#include "Kismet/GameplayStatics.h"

void ATwinStickShooter_CPPGameModeBase::RespawnPlayer()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	AHeroCharacter* HeroCharacter = GetWorld()->SpawnActor<AHeroCharacter>(BP_HeroCharacter, PlayerSpawnTransform.GetLocation(), PlayerSpawnTransform.Rotator(), SpawnParams);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController != nullptr)
	{
		PlayerController->Possess(HeroCharacter);
	}
}

