// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Destroyable.generated.h"

UCLASS()
class ADestroyable : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADestroyable();

    virtual void Tick(float DeltaTime) override;

    virtual void BeginDeathState() PURE_VIRTUAL(ADestroyable::BeginDeathState())

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
};