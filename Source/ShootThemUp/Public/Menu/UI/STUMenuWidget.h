// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuWidget.generated.h"

/**
 * 
 */

class UButton;
UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;
    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;
    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnStartGame();
    UFUNCTION()
    void OnQuitGame();
};
