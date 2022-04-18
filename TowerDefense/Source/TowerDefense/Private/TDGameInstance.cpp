// Fill out your copyright notice in the Description page of Project Settings.


#include "TDGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayHUDC_CPP.h"
#include "TurretTest.h"
#include "TD_PlayerPawn.h"
#include "Enemy.h"

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

TMap<FString, TSubclassOf<ATurretBase>> UTDGameInstance::GetPossibleTypesOfTurretsToBuild()
{
    TMap<FString, TSubclassOf<ATurretBase>> Result;

    Result.Add("Test Turret", ATurretTest::StaticClass());

    for (TObjectIterator<UClass> It; It; ++It)
    {
        if (It->IsChildOf(ATurretTest::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
        {
            UClass* ClassType = *It;
            //const FString ClassName = ClassType->GetName();
            ATurretBase* TurretBase = Cast<ATurretBase>(ClassType);
            const FString ClassName = TurretBase->GetName();
            Result.Add(ClassName, ClassType);
            UE_LOG(LogTemp, Warning, TEXT("Adding class: [%s]"), *ClassName);
        }
    }

    return Result;
}