#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

    class UCameraShakeBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    //virtual void Tick(float DeltaTime) override;
    // Sets default values for this component's properties
    USTUHealthComponent();
    float GetHealth() const { return Health; }
    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const { return Health / MaxHealth; }

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

    bool TryToHeal(float HealthPoint);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxHealth = 120.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    bool AutoHeal = true;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (Editcondition = "AutoHeal"))
    float HealModifier = 5.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (Editcondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (Editcondition = "AutoHeal"))
    float HealDelay = 3.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;



private:
   
    FTimerHandle HealTimerHandle;
    float Health = 0.0f;

        UFUNCTION(BlueprintCallable, Category = "Health")
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void HealUpdate();
    void SetHealth(float NewHealth);
    void PlayCameraShake();


};