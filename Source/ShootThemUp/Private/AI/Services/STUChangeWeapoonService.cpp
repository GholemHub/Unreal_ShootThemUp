// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Services/STUChangeWeapoonService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"

USTUChangeWeapoonService::USTUChangeWeapoonService() {}

void USTUChangeWeapoonService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    // const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (const auto Controller = OwnerComp.GetAIOwner())
    {
        if (const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn()))
        {
            float RandomValue = FMath::RandRange(0.0f, 1.0f);

            if (RandomValue < Probability)
            {
                // Event or action when the probability condition is met
                WeaponComponent->NextWeapon();
            }

            // HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
