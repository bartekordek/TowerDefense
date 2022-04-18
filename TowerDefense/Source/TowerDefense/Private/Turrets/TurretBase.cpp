// Fill out your copyright notice in the Description page of Project Settings.


#include "Turrets/TurretBase.h"

int32 ATurretBase::GetCost() const
{
    return m_Cost;
}

void ATurretBase::SetCost(int32 InCost)
{
    m_Cost = InCost;
}

FString ATurretBase::GetName()
{
    return TEXT("NONE");
}