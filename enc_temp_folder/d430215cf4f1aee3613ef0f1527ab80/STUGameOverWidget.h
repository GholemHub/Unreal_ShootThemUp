// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Develop/STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

/**
 * 
 */
class UVerticalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;
    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(ESTUMatchState State);

    void UpdatePlayersStat();
    UFUNCTION()
    void OnResetLevel();
};
