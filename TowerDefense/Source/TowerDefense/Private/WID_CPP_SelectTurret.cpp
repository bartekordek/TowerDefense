// Fill out your copyright notice in the Description page of Project Settings.


#include "WID_CPP_SelectTurret.h"

void UWID_CPP_SelectTurret::SelectCurrentStand(AActor* Stand)
{
    CurrentlySelectedStand = Stand;
}

UWID_CPP_SelectTurret::UWID_CPP_SelectTurret(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
    {
        UClass* Class = *ClassIt;

        // Only interested in native C++ classes
        FString Name = Class->GetFullName();
        UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Name);
        if (!Class->IsNative())
        {
            continue;
        }
    }
}

AActor* UWID_CPP_SelectTurret::GetCurrentStand()
{
    return CurrentlySelectedStand;
}