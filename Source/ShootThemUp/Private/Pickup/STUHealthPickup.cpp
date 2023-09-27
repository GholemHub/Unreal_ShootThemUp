// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead() || HealthComponent->GetHealthPercent() == 100.0)
        return false;

    auto Hilled = HealthComponent->TryToHeal(HealthPoints);
    if (Hilled)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation()); 
    }
    return Hilled;
}
