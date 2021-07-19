// Fill out your copyright notice in the Description page of Project Settings.

#include "WayPointHelper.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyWaypoint.h"

// Sets default values for this component's properties
UWayPointHelper::UWayPointHelper()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UWayPointHelper::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyWaypoint::StaticClass(), FoundActors);

    FoundActors.Sort([](const AActor& WP_0, const AActor& WP_1) {
        return WP_0.GetName() < WP_1.GetName();
	});

    for (const auto& Actor : FoundActors)
    {
        AEnemyWaypoint* EW = static_cast<AEnemyWaypoint*>(Actor);
        Waypoints.Enqueue(EW);
    }

    Parent = GetOwner();
}

bool UWayPointHelper::ActorIsOnPoint(const AActor& Actor)
{
    if (CurrentWaypoint == nullptr)
    {
        if (Waypoints.IsEmpty())
        {
            return false;
        }
        Waypoints.Peek(CurrentWaypoint);
        Waypoints.Pop();
    }
    auto Distance = CurrentWaypoint->GetDistanceTo(&Actor);
    return Distance < Epsilon;
}

void UWayPointHelper::MoveToNextWaypoint()
{
    if (Waypoints.IsEmpty() == false)
    {
        Waypoints.Peek(CurrentWaypoint);
        Waypoints.Pop();
    }
}

bool UWayPointHelper::ThereArePlacesTogo() const
{
    return !Waypoints.IsEmpty();
}

TOptional<FVector> UWayPointHelper::GetNextPosition()
{
    TOptional<FVector> Result;
    if (CurrentWaypoint == nullptr)
    {
        if (Waypoints.IsEmpty())
        {
            return Result;
        }

        AEnemyWaypoint* Value;
        Waypoints.Peek(Value);
        Waypoints.Pop();
        Result = Value->GetActorLocation();
        CurrentWaypoint = Value;
        return Result;
    }
    Result = CurrentWaypoint->GetActorLocation();
    return Result;
}


// Called every frame
void UWayPointHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}