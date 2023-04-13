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
    virtual void MakeShot() override;
	protected:
    

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float TimeBetweenShots = 0.1f;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float BulletSpread = 1.5f;

	private:
    FTimerHandle ShotTimerHandle;
        virtual bool GetTraceData(FVector&, FVector&) const override;
};
