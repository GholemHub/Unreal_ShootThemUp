// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "UI/STUHealthBarWidget.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;
class USTUHealthComponent;


/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()
	
public:
    ASTUAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    virtual void Tick(float DeltaTime) override;

	
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USTUHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    float HealthVisibilityDistance = 1000;

    virtual void OnDeath() override;
    virtual void OnHealthChanged(float Health, float HealthDelta) override;
    virtual void BeginPlay() override;

private:
    void UpdateHealthWdgetVisibility();
};
