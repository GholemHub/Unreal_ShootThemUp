// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUReturnToMainWidget.generated.h"

/**
 * 
 */

class UButton;
UCLASS()
class SHOOTTHEMUP_API USTUReturnToMainWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    UButton* RetrunToMenu;
public:
    UFUNCTION()
    void OnReturnToMenu();
};
