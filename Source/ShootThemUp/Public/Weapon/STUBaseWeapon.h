// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASTUBaseWeapon();
    virtual void StartFire();
    virtual void StopFire();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage")
    float DamageAmount = 10.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float TimeBetweenShots = 0.1f;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float BulletSpread = 1.5f;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    USkeletalMeshComponent* WeaponMesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    float TraceMaxDistance = 1500.0f;

	virtual void BeginPlay() override;

private:
    void MakeShot();
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector&, FRotator&)const;
    FVector GetMuzzleWorldLocation() const;
    void MakeDamage(const FHitResult& HitResult);
    FTimerHandle ShotTimerHandle;
    
};
