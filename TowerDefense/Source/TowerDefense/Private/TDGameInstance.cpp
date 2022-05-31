// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayHUDC_CPP.h"
#include "TurretTest.h"
#include "TD_PlayerPawn.h"
#include "Enemy.h"
#include "UObject/Class.h"

UTDGameInstance::UTDGameInstance()
{

}

void UTDGameInstance::SetMenuWidget(UUserWidget* MenuWidgetIn)
{
	MenuWidget = MenuWidgetIn;
}

void UTDGameInstance::SetHUDWidget(UGameplayHUDC_CPP* InWidget)
{
    HUDWidget = InWidget;
}

UGameplayHUDC_CPP* UTDGameInstance::GetHUDWidget()
{
    return HUDWidget;
}

void UTDGameInstance::SetPlayerPawn(ATD_PlayerPawn* InWidget)
{
    PlayerPawn = InWidget;
}

ATD_PlayerPawn* UTDGameInstance::GetPlayerPawn()
{
    return PlayerPawn;
}

void UTDGameInstance::DestroyMenu()
{
	if (MenuWidget)
	{
		MenuWidget->RemoveFromParent();
		MenuWidget = nullptr;
	}
}

void UTDGameInstance::DestroyHUDWidget()
{
    if (HUDWidget)
    {
        HUDWidget->RemoveFromParent();
        HUDWidget = nullptr;
    }
}

void UTDGameInstance::HurtPlayer(float Value, AActor* DamageCauser)
{
    //APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    APawn* InPlayerPawn = Cast<APawn>(PlayerPawn);
    UGameplayStatics::ApplyDamage(InPlayerPawn, Value, nullptr, DamageCauser, UDamageType::StaticClass());
}

void UTDGameInstance::SpawnEnemy(TSubclassOf<AEnemy> EnemyType)
{
    FVector Location(0.0f, 0.0f, 0.0f);
    FRotator Rotation(0.0f, 0.0f, 0.0f);
    GetWorld()->SpawnActor < AEnemy>(EnemyType, Location, Rotation);
}

UUserWidget* UTDGameInstance::CreateBuildMenu()
{
    if (!BuildWidget)
    {
        BuildWidget = CreateWidget<UUserWidget>(this, TypeOfBuildWidget, BuildWidgetname);
        BuildWidget->AddToViewport();
    }

    return BuildWidget;
}

void UTDGameInstance::DestroyBuildMenu()
{
    if (BuildWidget)
    {
        BuildWidget->RemoveFromParent();
        BuildWidget = nullptr;
    }
}

void UTDGameInstance::ToggleBuildingBlock(bool enableBlock)
{
    BuildingBlocked = enableBlock;
}

bool UTDGameInstance::GetIsBuildingBlocked() const
{
    return BuildingBlocked;
}

void UTDGameInstance::RegisterTurretType(const FString& ClassName, TSubclassOf<ATurretBase> TurretType)
{
    bool Contains = TypesOfTurretsAll.Contains(ClassName);
    if (Contains)
    {

    }
    else
    {
        TypesOfTurretsAll.Add(ClassName, TurretType);
    }
}

TMap<FString, TSubclassOf<ATurretBase>> UTDGameInstance::GetPossibleTypesOfTurretsToBuild()
{
    return TypesOfTurretsAll;
}

void UTDGameInstance::ResetTurretTypes()
{
    TypesOfTurretsAll.Empty();
}

void UTDGameInstance::SetCashValue(int32 Value)
{
    CurrentCashValue = Value;
}

int32 UTDGameInstance::GetCurrentCashValue()
{
    return CurrentCashValue;
}