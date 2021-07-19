#include "TurretTest.h"
#include "Enemy.h"
#include "Projectile.h"
#include <limits>
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATurretTest::ATurretTest()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Initialize();
}

void ATurretTest::Initialize()
{
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleColider"));
    RootComponent = CapsuleComp;

    Stand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    Stand->SetupAttachment(RootComponent);

    Barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
    Barrel->SetupAttachment(Stand);

    Motor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Motor"));
    Motor->SetupAttachment(Stand);

    Guard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Guard"));
    Guard->SetupAttachment(Stand);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(Barrel);
}

// Called when the game starts or when spawned
void ATurretTest::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (PlayerPawn)
    {
        auto PlayerController = PlayerPawn->GetController();
        if (PlayerController)
        {
            PlayerControllerRef = Cast<APlayerController>(PlayerController);
        }
    }

    GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurretTest::OnTimer, UpdateIntervalSeconds, true, 2.0f);
}

// Called every frame
void ATurretTest::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // if(PlayerControllerRef)
    // {
    //     FHitResult TraceHitResult;
    //     PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
    //     FVector HitLocation = TraceHitResult.ImpactPoint;

    //     RotateTurret(HitLocation);
    // }
}

void ATurretTest::BeginDeath()
{

}

void ATurretTest::OnTimer()
{
    auto NearestEnemy = GetNearestEnemy();
    if (NearestEnemy)
    {
        auto EnemeyPosition = NearestEnemy->GetActorLocation();
        RotateTurret(EnemeyPosition);
        if (IsInRange(NearestEnemy))
        {
            Fire();
        }
    }
}

void ATurretTest::BeginDeathState()
{

}

bool ATurretTest::IsInRange(AActor* Enemy) const
{
    return FVector::Dist(GetActorLocation(), Enemy->GetActorLocation()) <= ShootRange;
}

void ATurretTest::Fire()
{
    FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
    FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

    check(ProjectileClass);

    AProjectile* TempProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
    FActorSpawnParameters SpawnParams;
    //AProjectile* TempProjectile =
    //    GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
    TempProjectile->SetOwner(this);
}

void ATurretTest::RotateTurret(FVector LookAtTarget)
{
    FVector LookAtTargetCleaned = FVector(
        LookAtTarget.X,
        LookAtTarget.Y,
        CapsuleComp->GetComponentLocation().Z);
    FVector StartLocation = CapsuleComp->GetComponentLocation();

    auto RelativeLocation = LookAtTargetCleaned - StartLocation;
/*
    UE_LOG(LogTemp, Warning, TEXT("StartLocation location: %s"), *StartLocation.ToString());
    UE_LOG(LogTemp, Warning, TEXT("LookAtTargetCleaned location: %s"), *LookAtTargetCleaned.ToString());
    UE_LOG(LogTemp, Warning, TEXT("RelativeLocation location: %s"), *RelativeLocation.ToString());
    UE_LOG(LogTemp, Warning, TEXT("RelativeLocation Rotation P: %f"), RelativeLocation.Rotation().Pitch);
    UE_LOG(LogTemp, Warning, TEXT("RelativeLocation Rotation Y: %f"), RelativeLocation.Rotation().Yaw);
    UE_LOG(LogTemp, Warning, TEXT("RelativeLocation Rotation R: %f"), RelativeLocation.Rotation().Roll);
*/
    FRotator TurretRotation = RelativeLocation.Rotation();
    CapsuleComp->SetWorldRotation(TurretRotation);
}

AActor* ATurretTest::GetNearestEnemy()
{
    AActor* Result = nullptr;

    TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), Actors);

    float LastDistance = std::numeric_limits<float>::max();
    float DistanceToEnemy = std::numeric_limits<float>::max();
    for( auto i = 0; i < Actors.Num(); ++i )
    {
        AActor* CurrentActor = Actors[i];
        DistanceToEnemy = GetDistanceTo(CurrentActor);
        //UE_LOG(LogTemp, Warning, TEXT("Pos: [%s], Enemy Pos: [%s], DistanceToEnemy: [%f]"), *GetActorLocation().ToString(),
        //    *CurrentActor->GetActorLocation().ToString(), DistanceToEnemy);
        if (DistanceToEnemy < LookRange && DistanceToEnemy < LastDistance)
        {
            LastDistance = DistanceToEnemy;
            Result = CurrentActor;
        }
    }

    return Result;
}