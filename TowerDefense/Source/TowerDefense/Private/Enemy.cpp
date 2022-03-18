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
            FVector TargetPosition = NextPosition.GetValue();
            TargetPosition.Z = CurrentPos.Z;
            auto Result = TargetPosition - CurrentPos;
            Result.Normalize();
            Result *= MoveComponent;
            CurrentPos += Result;
            CurrentPos.Z = 2048;

            float Z = GetSurfaceHeight();
            //UE_LOG(LogTemp, Warning, TEXT("CurrentPos: %s"), *CurrentPos.ToString());
            UE_LOG(LogTemp, Warning, TEXT("Z: %f"), Z);
            CurrentPos.Z = Z + ZOffset;
        }
    }

    //TODO: rotate this shiet.
    CurrentRotation.Pitch = RotVal;
    RotVal += 4.f;

}

float AEnemy::GetSurfaceHeight()
{
    UWorld* World{this->GetWorld()};
    FHitResult HitResult;
    if (World)
    {
        FVector StartLocation{CurrentPos.X, CurrentPos.Y, 2048};    // Raytrace starting point.
        FVector EndLocation{CurrentPos.X, CurrentPos.Y, -1024};         // Raytrace end point.

        // Raytrace for overlapping actors.
        World->LineTraceSingleByObjectType(OUT HitResult, StartLocation, EndLocation,
            FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic), FCollisionQueryParams());
    }

    if (HitResult.GetActor())
    {
        //UE_LOG(LogTemp, Warning, TEXT("HitResult: %s"), *HitResult.ToString());
        return HitResult.ImpactPoint.Z;
    }
    else
    {
        return 0.f;
    }
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