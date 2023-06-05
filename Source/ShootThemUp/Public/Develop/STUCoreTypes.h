// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.generated.h"


/**
 * 
 */

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairIcon;
};
