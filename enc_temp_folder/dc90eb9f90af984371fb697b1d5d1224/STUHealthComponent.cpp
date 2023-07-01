#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraShakeBase.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool USTUHealthComponent::TryToHeal(float HealthPoint)
{

    if (Health != 0 && Health != MaxHealth)
    {
        SetHealth(Health + HealthPoint);
        UE_LOG(LogHealthComponent, Error, TEXT("Added health"));   
        return true;
    }
    else
    {
        UE_LOG(LogHealthComponent, Error, TEXT("Not Added health"));   
        return false;
    }
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
    //PlayCameraShake();
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

void USTUHealthComponent::PlayCameraShake() 
{
    if(IsDead()) return;
    const auto Player = Cast<APawn>(GetOwner());
    if (!Player)
        return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager)
        return; 
    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}
