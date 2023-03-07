// Shoot Them Up Game, All Rights Receved


#include "Components/TestHealthComponent.h"

// Sets default values for this component's properties
UTestHealthComponent::UTestHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTestHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

