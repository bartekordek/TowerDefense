// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"


class UCapsuleComponent;
class UWayPointHelper;
class AEnemyWaypoint;

UCLASS()
class AEnemy: public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AEnemy();
    virtual void Tick(float DeltaTime) override;
    void MoveTo(const FVector& In);

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    void Move();

    float GetSurfaceHeight();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UCapsuleComponent* CapsuleComp = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BaseMesh = nullptr;
	// Called every frame

    UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
    float MoveComponent = 0.5f;

    FVector CurrentPos;
    FRotator CurrentRotation;

    UWayPointHelper* WayPointHelper;

    UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
    float TimeDelta = 0.01f;
    float Time = 0.0f;

    UPROPERTY(EditAnywhere, Category = "Move", meta = (AllowPrivateAccess = "true"))
    float TimerDelta = 0.01;
    float RotVal = 0.0f;

    FTimerHandle TimerHandle;

    bool PlayerHurt = false;


    UPROPERTY(EditAnywhere, Category = "Damage", meta = (AllowPrivateAccess = "true"))
    float BaseDamage = 25.f;

    UPROPERTY(EditAnywhere, Category = "Position", meta = (AllowPrivateAccess = "true"))
    float ZOffset = 100.f;
};