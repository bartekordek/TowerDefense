#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}


void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    AActor* Owner = GetOwner();
    UE_LOG(LogTemp, Warning, TEXT("[%s] Registering Health Component."), *Owner->GetFullName());
    CurrentHealth = HealthMax;
    Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
    if (Damage <= 0.f)
    {
        return;
    }

    CurrentHealth -= Damage;
    const FString DamagedActorName = DamagedActor->GetFullName();
    UE_LOG(LogTemp, Warning, TEXT("[%s] OUCH!"), *DamagedActorName);

    OnPlayerHitDelegate.Broadcast(CurrentHealth);

    if (DieOnZeroHP && CurrentHealth <= 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("[%s] I DIE!!"), *DamagedActorName);
        DamagedActor->Destroy();
    }
}

float UHealthComponent::GetCurrentHealth() const
{
    return CurrentHealth;
}

float UHealthComponent::GetMaxHealth() const
{
    return HealthMax;
}

void UHealthComponent::ToggleDeathOnZeroHP(bool Enable)
{
    DieOnZeroHP = Enable;
}