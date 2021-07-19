// Fill out your copyright notice in the Description page of Project Settings.


#include "TD_HealthComponent.h"

// Sets default values for this component's properties
UTD_HealthComponent::UTD_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTD_HealthComponent::BeginPlay()
{
    Super::BeginPlay();

    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UTD_HealthComponent::DamageTaken);
    UE_LOG(LogTemp, Warning, TEXT("BeginPlay: %s"), *GetName());
}


// Called every frame
void UTD_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UTD_HealthComponent::DamageTaken(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
    UE_LOG(LogTemp, Warning, TEXT("DamagedActor: %s"), *DamagedActor->GetName());
    if (Damage <= 0.f)
        return;

    CurrentHealth -= Damage;
    UE_LOG(LogTemp, Warning, TEXT("Health: %f"), CurrentHealth);

    if (CurrentHealth <= 0.0f)
    {
        DamagedActor->Destroy();
    }
}