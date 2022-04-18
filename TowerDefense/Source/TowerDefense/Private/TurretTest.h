// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Turrets/TurretBase.h"
#include "TurretTest.generated.h"

class AProjectile;
class UCapsuleComponent;

UCLASS()
class ATurretTest : public ATurretBase
{
    GENERATED_BODY()

public:
    ATurretTest();

    virtual void Tick(float DeltaTime) override;

    void BeginDeath();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void RotateTurret(FVector LookAtTarget);

private:
    void Initialize();
    AActor* GetNearestEnemy();
    bool IsInRange(AActor* Enemy) const;
    void Fire();

    void OnTimer();

    void BeginDeathState() override;

    static FString GetName() override;

    APlayerController* PlayerControllerRef = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCapsuleComponent* CapsuleComp = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* Stand = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* Barrel = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* Motor = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* Guard = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USceneComponent* ProjectileSpawnPoint = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
    float LookRange = 2048.f;

    UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
    float ShootRange = 1024.f;

    UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
    float UpdateIntervalSeconds = 0.125;

    FTimerHandle TimerHandle;
    FTimerDelegate TimerDelegate;

};