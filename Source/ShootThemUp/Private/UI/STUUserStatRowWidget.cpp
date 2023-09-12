// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUUserStatRowWidget.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUUserStatRowWidget::SetPlayerName(const FText& Text) {
    if (!PlayerNameTextBlock)
        return;
    PlayerNameTextBlock->SetText(Text);
}
void USTUUserStatRowWidget::SetKills(const FText& Text) {
    if (!KillsTextBlock)
        return;
    KillsTextBlock->SetText(Text);
}
void USTUUserStatRowWidget::SetDeaths(const FText& Text) {
    if (!DeathsTextBlock)
        return;
    DeathsTextBlock->SetText(Text);
}
void USTUUserStatRowWidget::SetTeam(const FText& Text) {
    if (!TeamTextBlock)
        return;
    TeamTextBlock->SetText(Text);
}

void USTUUserStatRowWidget::SetPlayerIndicatorVisibility(bool Visiable) {
    if (!PlayerIndicatorImage)
        return;
    PlayerIndicatorImage->SetVisibility(Visiable ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
