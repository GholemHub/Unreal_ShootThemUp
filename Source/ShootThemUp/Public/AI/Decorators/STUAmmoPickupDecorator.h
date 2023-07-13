// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUAmmoPickupDecorator.generated.h"

/**
 * 
 */

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API USTUAmmoPickupDecorator : public UBTDecorator
{
	GENERATED_BODY()
protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ASTUBaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
