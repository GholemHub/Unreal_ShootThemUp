// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/STUAmmoPickup.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"


bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthCimponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if (!HealthCimponent || HealthCimponent->IsDead())
        return false;

    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
        return false;

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
