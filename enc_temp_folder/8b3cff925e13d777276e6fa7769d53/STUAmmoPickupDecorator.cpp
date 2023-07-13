// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/STUAmmoPickupDecorator.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"
#include "AIController.h"


bool USTUAmmoPickupDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeapon()->IsAmmoEmpty();
}