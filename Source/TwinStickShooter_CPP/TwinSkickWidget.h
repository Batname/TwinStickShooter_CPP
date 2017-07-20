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
	UFUNCTION(BlueprintCallable, Category = HeroHealth)
	float GetHeroHealth();

	UFUNCTION(BlueprintCallable, Category = HeroScore)
	FText GetHeroScore();

private:
};
