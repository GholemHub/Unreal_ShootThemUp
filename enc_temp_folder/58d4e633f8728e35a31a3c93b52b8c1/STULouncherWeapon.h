// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STULouncherWeapon.generated.h"

/**
 * 
 */

class ASTUProjectile;


UCLASS()
class SHOOTTHEMUP_API ASTULouncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTUProjectile> ProjectileClass;
    virtual void MakeShot() override;
	
};
