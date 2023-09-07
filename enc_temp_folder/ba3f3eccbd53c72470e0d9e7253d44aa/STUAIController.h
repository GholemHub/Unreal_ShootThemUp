// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

/**
 * 
 */
class USTUAIPerceptionComponent;
UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
    GENERATED_BODY()

    ASTUAIController();


protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    USTUAIPerceptionComponent* STUAIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float Deltatime) override;

private:
    AActor* GetFocusOnActor() const;

};
