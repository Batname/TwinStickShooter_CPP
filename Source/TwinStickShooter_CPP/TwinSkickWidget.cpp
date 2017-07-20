// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinSkickWidget.h"
#include "BaseCharacter.h"
#include "TwinStickShooter_CPPGameModeBase.h"
#include "EnemySpawner.h"


#include "Kismet/GameplayStatics.h"


void UTwinSkickWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameModeBase = Cast<ATwinStickShooter_CPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

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
	if (GameModeBase != nullptr)
	{
		return FText::AsNumber(GameModeBase->GetScore());
	}

	return FText::GetEmpty();
}

FText UTwinSkickWidget::GetEnemiesCount()
{
	if (GameModeBase != nullptr && GameModeBase->GetEnemySpawner() != nullptr)
	{
		return FText::AsNumber(GameModeBase->GetEnemySpawner()->GetEnemiesOnScene());
	}


	return FText::GetEmpty();

}