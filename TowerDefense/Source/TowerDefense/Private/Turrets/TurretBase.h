// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destroyable.h"
#include "TurretBase.generated.h"

class AProjectile;
class UCapsuleComponent;


UCLASS()
class ATurretBase : public ADestroyable
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable)
    int32 GetCost() const;

    UFUNCTION(BlueprintCallable)
    void SetCost(int32 InCost);

protected:
private:
    int32 m_Cost = 0;
};