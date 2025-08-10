// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"

#include "MyMassProcessor.generated.h"

/**
 *
 */
UCLASS()
class UGravityProcessor : public UMassProcessor
{
    GENERATED_BODY()

public:
    UGravityProcessor();

protected:
private:
    void ConfigureQueries(const TSharedRef<FMassEntityManager>& InMsMgr) override;
    void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

    FMassEntityQuery GravityEntityQuery;
};

UCLASS()
class UMovementProcessor : public UMassProcessor
{
    GENERATED_BODY()

public:
    UMovementProcessor();

protected:
private:
    void ConfigureQueries(const TSharedRef<FMassEntityManager>& InMsMgr) override;
    void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

    FMassEntityQuery MovementQuery;
};
