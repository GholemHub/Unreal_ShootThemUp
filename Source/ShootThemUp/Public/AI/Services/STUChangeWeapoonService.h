// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUChangeWeapoonService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUChangeWeapoonService : public UBTService
{
	GENERATED_BODY()
	
USTUChangeWeapoonService();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Probability;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
