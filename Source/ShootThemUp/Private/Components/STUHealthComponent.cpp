#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Develop/STUIceDamageType.h"
#include "Develop/STUFireDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)
USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;
    UE_LOG(LogHealthComponent, Display, TEXT("Damage %f"), Damage)

    if (DamageType)
    {
        if (DamageType->IsA<USTUFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("So hoooot !!!"));
        }
        else if (DamageType->IsA<USTUIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("So COOld !!!"));
        }
    }
}