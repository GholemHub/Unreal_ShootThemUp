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
    virtual void Fire();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    USkeletalMeshComponent* WeaponMesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    float TraceMaxDistance = 1500.0f;

	virtual void BeginPlay() override;

private:
    void MakeShot();
};
