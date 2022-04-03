// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WID_CPP_SelectTurret.generated.h"

/**
 * 
 */
UCLASS()
class UWID_CPP_SelectTurret : public UUserWidget
{
	GENERATED_BODY()

public:
    UWID_CPP_SelectTurret(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    AActor* GetCurrentStand();

	UFUNCTION(BlueprintCallable)
    void SelectCurrentStand(AActor* Stand);

protected:

private:
    AActor* CurrentlySelectedStand = nullptr;
};