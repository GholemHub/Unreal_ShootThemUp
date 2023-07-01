// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Develop/STUCoreTypes.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 * 
 */

class USTUHealthComponent;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPervent() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponUIData(FWeaponUIData& UIData) const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIAmmoData(FAmmoData& AmmoUIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

    virtual bool Initialize() override;

private:
    USTUHealthComponent* GetHealthComponent() const;
    void OnHealthCanged(float Health, float HealthDelta);
};
