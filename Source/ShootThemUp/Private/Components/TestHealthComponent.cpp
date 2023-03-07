// Shoot Them Up Game, All Rights Receved


#include "Components/TestHealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UTestHealthComponent::UTestHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTestHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UTestHealthComponent::OnTakeAnyDamage);
    }
	Health = MaxHealth;
}

void UTestHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;
}

