// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/STUAmmoPickup.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogTemp, Error, TEXT("USTUWeaponComponent::TryToAddAmmo"));
    const auto HealthCimponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if (!HealthCimponent || HealthCimponent->IsDead())
        return false;

    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
        return false;
    auto Added = WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
    if (Added)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
    }
    return Added;
}
