// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMassProcessor.h"
#include "MassMovementFragments.h"
#include "MassExecutionContext.h"
#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassEntity/BasicTypes.h"

UE_DISABLE_OPTIMIZATION

UGravityProcessor::UGravityProcessor()
{
    // This executes on any type of game client (server, standalone, client etc).
    ExecutionFlags = (int32) (EProcessorExecutionFlags::All);
    // You can combine flags if you want:
    // ExecutionFlags = (int32)(EProcessorExecutionFlags::Client | EProcessorExecutionFlags::Standalone);

    // Using the built-in movement processor group, we want to execute before it does!
    ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Movement);
}

void UGravityProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& InMsMgr)
{
    GravityEntityQuery.Initialize(InMsMgr);
    GravityEntityQuery.AddTagRequirement<FMSGravityTag>(EMassFragmentPresence::All);
    GravityEntityQuery.AddRequirement<FMassVelocityFragment>(EMassFragmentAccess::ReadWrite);
    GravityEntityQuery.RegisterWithProcessor(*this);
}

void UGravityProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
    float GravityZ = GetWorld()->GetGravityZ();
    GravityEntityQuery.ForEachEntityChunk(Context,
        [GravityZ](FMassExecutionContext& Context)
        {
            const int32 NumEntities = Context.GetNumEntities();
            TArrayView<FMassVelocityFragment> TransformList = Context.GetMutableFragmentView<FMassVelocityFragment>();
            for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
            {
                FVector& Velocity = TransformList[EntityIndex].Value;

                Velocity += FVector(0, 0, GravityZ) * Context.GetDeltaTimeSeconds();
            }
        });
}


UMovementProcessor::UMovementProcessor()
{
    ExecutionFlags = (int32) (EProcessorExecutionFlags::All);
    ExecutionOrder.ExecuteInGroup = UE::Mass::ProcessorGroupNames::Movement;
}

void UMovementProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
    MovementQuery.Initialize(EntityManager);

    MovementQuery.AddTagRequirement<FMSBasicMovementTag>(EMassFragmentPresence::All);
    MovementQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
    MovementQuery.AddRequirement<FMassForceFragment>(EMassFragmentAccess::ReadOnly);
    MovementQuery.AddRequirement<FMassVelocityFragment>(EMassFragmentAccess::ReadWrite);
    MovementQuery.RegisterWithProcessor(*this);
}

void UMovementProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
    MovementQuery.ForEachEntityChunk(Context,
        [](FMassExecutionContext& Context)
        {
            QUICK_SCOPE_CYCLE_COUNTER(STAT_MASS_MovementEntityQuery);

            const int32 NumEntities = Context.GetNumEntities();

            const TArrayView<FTransformFragment> TransformList = Context.GetMutableFragmentView<FTransformFragment>();

            // This one is readonly, so we don't need Mutable
            const TConstArrayView<FMassForceFragment> ForceList = Context.GetFragmentView<FMassForceFragment>();

            const TArrayView<FMassVelocityFragment> VelocityList = Context.GetMutableFragmentView<FMassVelocityFragment>();

            float DeltaTime = Context.GetDeltaTimeSeconds();

            // Loop over every entity in the current chunk and do stuff!
            for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
            {
                FTransform& TransformToChange = TransformList[EntityIndex].GetMutableTransform();

                const FVector& Force = ForceList[EntityIndex].Value;

                FVector& Velocity = VelocityList[EntityIndex].Value;

                // Force steers the velocity
                Velocity += Force * DeltaTime;

                // Move the actual transform
                TransformToChange.AddToTranslation(Velocity * DeltaTime);
            }
        });
}

UE_ENABLE_OPTIMIZATION