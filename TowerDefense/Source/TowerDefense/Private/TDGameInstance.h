// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TDGameInstance.generated.h"

class UUserWidget;
class UGameplayHUDC_CPP;
class ATD_PlayerPawn;
class AEnemy;

/**
 *
 */
UCLASS()
class UTDGameInstance : public UGameInstance
{
    GENERATED_BODY()
public:
    UTDGameInstance();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void CreateMenu();

    UFUNCTION(BlueprintCallable)
    void DestroyMenu();

    UFUNCTION(BlueprintCallable)
    void SetMenuWidget(UUserWidget* MenuWidgetIn);

    UFUNCTION(BlueprintCallable)
    void SetHUDWidget(UGameplayHUDC_CPP* InWidget);

    UFUNCTION(BlueprintCallable)
    void SetPlayerPawn(ATD_PlayerPawn* InWidget);

    UFUNCTION(BlueprintCallable)
    void HurtPlayer(float Value, AActor* DamageCauser);

    UFUNCTION(BlueprintCallable)
    void DestroyHUDWidget();

    UFUNCTION(BlueprintCallable)
    UGameplayHUDC_CPP* GetHUDWidget();

    UFUNCTION(BlueprintCallable)
    ATD_PlayerPawn* GetPlayerPawn();

    UFUNCTION(BlueprintCallable)
    void SpawnEnemy(TSubclassOf<AEnemy> EnemyType);

protected:
private:
    UUserWidget* MenuWidget = nullptr;
    UGameplayHUDC_CPP* HUDWidget = nullptr;
    ATD_PlayerPawn* PlayerPawn = nullptr;

};