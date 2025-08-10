// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "SImpleRandomMovementTrait.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API USImpleRandomMovementTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()
	
protected:
    void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
	
	
};
