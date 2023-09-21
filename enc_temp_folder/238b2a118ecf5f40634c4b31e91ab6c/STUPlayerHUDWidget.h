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
class UProgressBar;


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
    int32 GetKillsUIAmmoData() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetRoundUIData() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetRoundTimerUIAmmoData() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

    virtual void NativeOnInitialized() override;

   /* UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    FString FormatBulets(int32 BulletsNum) const;*/
    


protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;

private:
    USTUHealthComponent* GetHealthComponent() const;
    void OnHealthCanged(float Health, float HealthDelta);

    void OnNewPawn(APawn* NewPawn);

    void UpdateHealthBar();
};