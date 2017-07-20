// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinSkickWidget.h"
#include "BaseCharacter.h"
#include "TwinStickShooter_CPPGameModeBase.h"


#include "Kismet/GameplayStatics.h"


float UTwinSkickWidget::GetHeroHealth()
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (BaseCharacter != nullptr)
	{
		return BaseCharacter->Health / 100;
	}

	return 0.f;
}

FText UTwinSkickWidget::GetHeroScore()
{
	ATwinStickShooter_CPPGameModeBase* GameModeBase = Cast<ATwinStickShooter_CPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GameModeBase != nullptr)
	{
		return FText::AsNumber(GameModeBase->GetScore());

	}

	return FText::GetEmpty();
}