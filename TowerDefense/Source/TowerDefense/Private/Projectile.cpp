#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Mesh"));
    RootComponent = Mesh;

    Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    Movement->InitialSpeed = Speed;
    Movement->MaxSpeed = Speed;
    InitialLifeSpan = 4.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

    //UE_LOG(
    //    LogTemp,
    //    Warning,
    //    TEXT("NAME: [%s], MAX SPEED: [%f], INITIAL SPEED: [%f]"),
    //    *GetName(), Movement->MaxSpeed,
    //    Movement->InitialSpeed
    //);

    Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("NAME: [%s], POS: [%s]"), *GetName(), *GetActorLocation().ToString());
}

void AProjectile::SetSender(AActor* Actor)
{
    Sender = Actor;
}

void AProjectile::OnHit(
    UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    //UE_LOG(LogTemp, Warning, TEXT("OnHit"));
    //UE_LOG(LogTemp, Warning, TEXT("HitComp: %s"), *HitComp->GetName());
    //UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName());
    //UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName());

   	auto MyOwner = GetOwner();
    if( MyOwner == nullptr )
    {
        return;
    }

    auto MyOwnerInstigator = MyOwner->GetInstigatorController();
    auto DamageTypeClass = UDamageType::StaticClass();

    if (OtherActor && OtherActor != this && OtherActor != MyOwner)
    {
        UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
        Destroy();
    }
}