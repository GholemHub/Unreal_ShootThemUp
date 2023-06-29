// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    virtual void MakeShot() override;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
    float DamageAmount = 10.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float TimeBetweenShots = 0.1f;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float BulletSpread = 1.5f;
    virtual bool GetTraceData(FVector&, FVector&) const override;

private:
    FTimerHandle ShotTimerHandle;
    void MakeDamage(const FHitResult& HitResult);
};
