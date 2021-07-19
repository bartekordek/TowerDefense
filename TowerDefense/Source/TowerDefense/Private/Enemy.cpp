// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "WayPointHelper.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TDGameInstance.h"

#include <limits>

AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = true;


    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleColider"));
    RootComponent = CapsuleComp;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(RootComponent);
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    UActorComponent* Component = GetComponentByClass(UWayPointHelper::StaticClass());
    WayPointHelper = Cast<UWayPointHelper>(Component);
    Component->GetOwner();

    TOptional<FVector> NextPosition = WayPointHelper->GetNextPosition();

    if (NextPosition.IsSet())
    {
        MoveTo(NextPosition.GetValue());
    }

    GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemy::Move, TimerDelta, true, 2.0f);

    BaseMesh->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
}

void AEnemy::Move()
{
    if (WayPointHelper->ActorIsOnPoint(*this))
    {
        if (WayPointHelper->ThereArePlacesTogo())
        {
            WayPointHelper->MoveToNextWaypoint();
        }
        else
        {
            if (!PlayerHurt)
            {
                auto GameInstance = Cast <UTDGameInstance>( UGameplayStatics::GetGameInstance(this) );
                GameInstance->HurtPlayer(BaseDamage, this);
                Destroy();
                PlayerHurt = true;
            }
        }
    }
    else
    {
        TOptional<FVector> NextPosition = WayPointHelper->GetNextPosition();
        if (NextPosition.IsSet())
        {
            FVector Dupa;
            const FVector& TargetPosition = NextPosition.GetValue();
            auto Result = TargetPosition - CurrentPos;
            Result.Normalize();
            Result *= MoveComponent;
            CurrentPos += Result;
        }
    }

    //TODO: rotate this shiet.
    CurrentRotation.Pitch = RotVal;
    RotVal += 4.f;
    
    
    //UE_LOG(LogTemp, Warning, TEXT("Rotation: [%s]"), *CurrentRotation.ToString());
}

void AEnemy::MoveTo(const FVector& In)
{
    CurrentPos = In;
    SetActorRelativeLocation(CurrentPos, false, nullptr, ETeleportType::None);
    
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //AddActorLocalOffset(DeltaMove, true);
    //AddActorLocalTransform(CurrentPos);

    //SetActorLocationAndRotation(CurrentPos, CurrentRotation);

    SetActorLocation(CurrentPos);
    BaseMesh->SetRelativeRotation(CurrentRotation);

    //SetActorRelativeLocation(CurrentPos);
    //BaseMesh->SetWorldRotation(CurrentRotation);

    //CurrentPos.X = XOff + XAmp * sin(Time);
    //CurrentPos.Y = YOff + YAmp * cos(Time);
    //CurrentPos.Z = ZOff + ZAmp * cos(Time);


    Time += TimeDelta;
}

void AEnemy::OnHit(
    UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("OnHit"));
    UE_LOG(LogTemp, Warning, TEXT("HitComp: %s"), *HitComp->GetName());
    UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName());
    UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName());
}