// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

//DECLARE_LOG_CATEGORY_EXTERN(BaseCharacterLog, All, All)

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTestHealthComponent;
class UTextRenderComponent;

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
		UTestHealthComponent* TestHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
        UTextRenderComponent* TestRender;
	/* UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USTUHealthComponent* HealthComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* HealthTextComponent;*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;
    UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;


private:
    bool WantsToRun = false;
    bool IsMovingForward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartRunning();
    void OnStopRunning();

	UFUNCTION(BlueprintCallable, Category = "Movement")
    void OnTakeAnyDamageHandle(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
