#pragma once

#include "CoreMinimal.h"

#include "MassEntityTypes.h"

#include "BasicTypes.generated.h"

USTRUCT(BlueprintType)
struct FMSGravityTag : public FMassTag
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FMSBasicMovementTag : public FMassTag
{
    GENERATED_BODY()
};
