// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float Percent) 
{
    if (!HealthProgressBar)
        return;
    const auto HealthBarVisibilityy =
        (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)) ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealthBarVisibilityy);

    const auto HealthBarColor = Percent > PercentColor ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}