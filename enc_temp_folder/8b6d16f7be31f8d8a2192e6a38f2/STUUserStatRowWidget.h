// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUUserStatRowWidget.generated.h"

/**
 * 
 */

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUUserStatRowWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetDeaths(const FText& Text);
    void SetTeam(const FText& Text);

    void SetPlayerIndicatorVisibility(bool Visiable);
    void SetTeamColor(const FLinearColor& Color);

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathsTextBlock;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock;

	UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorImage;

    UPROPERTY(meta = (BindWidget))
    UImage* TeamImage;
};
