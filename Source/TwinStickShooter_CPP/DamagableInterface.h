// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamagableInterface.generated.h"

/**
 * 
 */
// UCLASS()
// class TWINSTICKSHOOTER_CPP_API UDamagableInterface : public UObject
// {
// 	GENERATED_BODY()
	
	
	
	
// };


UINTERFACE(Blueprintable)
class UDamagableInterface : public UInterface
{
    GENERATED_BODY()
};


class IDamagableInterface
{    
    GENERATED_BODY()

public:
    UFUNCTION(Category="DamagableInterface")
    virtual void AffectHealth(float Delta);
};