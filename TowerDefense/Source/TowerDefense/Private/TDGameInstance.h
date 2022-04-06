// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Turrets/TurretBase.h"
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

    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> TypeOfBuildWidget;

    UFUNCTION(BlueprintCallable)
    UUserWidget* CreateBuildMenu();

    UFUNCTION(BlueprintCallable)
    void DestroyBuildMenu();

    UFUNCTION(BlueprintCallable)
    void ToggleBuildingBlock(bool enableBlock);

    UFUNCTION(BlueprintCallable)
    bool GetIsBuildingBlocked() const;

    UFUNCTION(BlueprintCallable)
    TMap<FString, TSubclassOf<ATurretBase>> GetPossibleTypesOfTurretsToBuild();

protected:
private:
    UUserWidget* MenuWidget = nullptr;
    UUserWidget* BuildWidget = nullptr;
    UGameplayHUDC_CPP* HUDWidget = nullptr;
    ATD_PlayerPawn* PlayerPawn = nullptr;

    FName BuildWidgetname = L"BuildWidget";

    bool BuildingBlocked = false;

    TMap<FString, TSubclassOf<ATurretBase>> TypesOfTurretsAll;
};