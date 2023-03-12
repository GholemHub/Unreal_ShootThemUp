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

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
    USkeletalMeshComponent* WeaponMesh;

	virtual void BeginPlay() override;

};
