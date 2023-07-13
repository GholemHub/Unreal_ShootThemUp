// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickipCoildBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PickipCoildBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public:
    UEnvQueryTest_PickipCoildBeTaken(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
