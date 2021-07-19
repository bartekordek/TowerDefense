// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TD_HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTD_HealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UTD_HealthComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION()
    void DamageTaken(
        AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);


protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
    float MaxHealth = 120.f;
    float CurrentHealth = 120.f;
};