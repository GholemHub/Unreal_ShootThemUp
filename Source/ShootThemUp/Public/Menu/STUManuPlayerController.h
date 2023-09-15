// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUManuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUManuPlayerController : public APlayerController
{
	GENERATED_BODY()

		protected:
    virtual void BeginPlay() override;
	
};
