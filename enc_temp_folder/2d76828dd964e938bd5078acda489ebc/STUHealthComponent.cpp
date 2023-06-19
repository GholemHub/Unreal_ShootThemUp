#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    SetHealth(MaxHealth);

    check(MaxHealth > 0);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    
    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
}

void USTUHealthComponent::HealUpdate() {
    SetHealth(Health + HealModifier);
    
    if (Health==MaxHealth && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }

}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    UE_LOG(LogHealthComponent, Error, TEXT("HERE is %f"), Health);
    OnHealthChanged.Broadcast(Health);
}
