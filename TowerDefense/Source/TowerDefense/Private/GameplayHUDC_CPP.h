// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayHUDC_CPP.generated.h"

/**
 * 
 */
UCLASS()
class UGameplayHUDC_CPP : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetBaseHealth(float Value);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetCashValue(int32 CashIn);

protected:
private:
};