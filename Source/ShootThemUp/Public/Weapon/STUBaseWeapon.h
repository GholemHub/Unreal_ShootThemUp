// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Clips;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite;
};

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:	
	
	ASTUBaseWeapon();
    virtual void StartFire();
    virtual void StopFire();
    virtual void MakeShot();

protected:
    
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    USkeletalMeshComponent* WeaponMesh;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

	virtual void BeginPlay() override;
    virtual bool GetTraceData(FVector&, FVector&) const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector&, FRotator&)const;
    FVector GetMuzzleWorldLocation() const;

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    void ChangeClip();
    void LogAmmo();

private:
    FAmmoData CurrentAmmo;
};
