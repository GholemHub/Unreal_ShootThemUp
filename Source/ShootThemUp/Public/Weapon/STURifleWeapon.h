// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void Zoom(bool Enabled) override;

protected:
    virtual void MakeShot() override;
    ASTURifleWeapon();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float DamageAmount = 10.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire")
    float TimeBetweenShots = 0.1f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire")
    float BulletSpread = 1.5f;
    virtual bool GetTraceData(FVector&, FVector&) const override;

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VFX")
    USTUWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trace")
    UNiagaraSystem* TraceFX;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trace")
    FString TraceTargetName = "TraceTarget";
    UPROPERTY(EditDefaultsOnly, Category = "Zoom")
    float FOVZoomAngle = 50.0f;

private:
    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;
    AController* GetController() const;

    FTimerHandle ShotTimerHandle;
    void MakeDamage(const FHitResult& HitResult);
    void InitFX();
    void SetFXActive(bool Visable);
    UPROPERTY()
    UAudioComponent* FireAudioComponent;

    float DefaultCameraFOV = 90.0f;
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
};
