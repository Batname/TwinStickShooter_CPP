// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TwinSkickWidget.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKSHOOTER_CPP_API UTwinSkickWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;


	UFUNCTION(BlueprintCallable, Category = HeroHealth)
	float GetHeroHealth();

	UFUNCTION(BlueprintCallable, Category = HeroScore)
	FText GetHeroScore();

	UFUNCTION(BlueprintCallable, Category = EnemiesCount)
	FText GetEnemiesCount();

private:
	class ATwinStickShooter_CPPGameModeBase* GameModeBase;
};
