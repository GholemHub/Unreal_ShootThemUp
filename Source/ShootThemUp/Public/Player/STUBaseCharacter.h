// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Placement/STU_PlacementActorComponent.h"
#include "STUBaseCharacter.generated.h"


//DECLARE_LOG_CATEGORY_EXTERN(BaseCharacterLog, All, All)

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class USTUWeaponComponent;
class USTU_PlacementActorComponent;
class USTU_PlaceActorComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
    ASTUBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArmComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
        USTUHealthComponent* STUHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
        UTextRenderComponent* TestRender;
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMintage;

    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D LandedVectorVelocity = FVector2D(900.0f, 1200.0f);
    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUWeaponComponent* WeaponComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTU_PlacementActorComponent* PlacementComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTU_PlaceActorComponent* PlaceActorComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = "Movement")
    FName MaterialColorName = "Paint Color";

    virtual void OnDeath();
  

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;
    UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor& Color);

private:
    bool WantsToRun = false;
    bool IsMovingForward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartRunning();
    void OnStopRunning();
    void OnHealthChanged(float Health, float HealthDelta);
    void OnStartFire();
    void OnPlacementPressed();
    UFUNCTION(BlueprintCallable)
    void OnGroundLanded(const FHitResult& Hit);

    bool bIsBuilding = true;

};
