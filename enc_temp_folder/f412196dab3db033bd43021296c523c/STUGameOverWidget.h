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

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual bool Initialize() override;

protected:
    UPROPERTY()
    UVerticalBox* PlayerStatBox;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTUGameOverWidget> PlayerStatRowWidgetClass;

private:
    void OnMatchStateChanged(ESTUMatchState State);

    void UpdatePlayersStat(); 


    

};
