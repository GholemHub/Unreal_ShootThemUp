// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    FString Print = "Hello Game";
};
