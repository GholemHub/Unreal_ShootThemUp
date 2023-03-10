#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

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

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxHealth = 120.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    float HealModifier = 5.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    bool AutoHeal = true;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    float HealUpdateTime = 1.0f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    float HealDelay = 3.0f;


private:
   
    FTimerHandle HealTimerHandle;
    float Health = 0.0f;

        UFUNCTION(BlueprintCallable, Category = "Health")
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void HealUpdate();
    void SetHealth(float NewHealth);
};