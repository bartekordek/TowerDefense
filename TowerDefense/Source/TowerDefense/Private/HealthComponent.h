// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHitDelegate, float, NewBaseHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    float GetCurrentHealth() const;

    UFUNCTION(BlueprintCallable)
    float GetMaxHealth() const;

    UFUNCTION(BlueprintCallable)
    void ToggleDeathOnZeroHP(bool Enable);

    UPROPERTY(BlueprintAssignable)
    FOnPlayerHitDelegate OnPlayerHitDelegate;

    UPROPERTY(BlueprintAssignable)
    FOnDeathDelegate OnDeathDelegate;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    UFUNCTION()
    void DamageTaken(
        AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

    UPROPERTY(EditAnywhere, Category = "Value", meta = (AllowPrivateAccess = "true"))
    float HealthMax = 100.f;

    float CurrentHealth = 100.f;

    bool DieOnZeroHP = true;
};