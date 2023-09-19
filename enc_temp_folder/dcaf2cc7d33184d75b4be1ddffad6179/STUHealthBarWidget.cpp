// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float Percent, bool IsDead)
{
    if (!HealthProgressBar)
        return;

    const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold 
        ||FMath::IsNearlyZero(Percent)) 
        ? ESlateVisibility::Hidden : ESlateVisibility::Visible;

    HealthProgressBar->SetVisibility(HealthBarVisibility);
    const auto DeathBool = IsDead ? ESlateVisibility::Hidden: ESlateVisibility::Visible;
    if (!IsDead)
    {
        UE_LOG(LogTemp, Error, TEXT("Percent %i"), DeathBool);
        HealthProgressBar->SetVisibility(DeathBool);
    }
    

    const auto HealthBarColor = Percent > PercentColor ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
    //UE_LOG(LogTemp, Error, TEXT("Percent %f"), Percent);
}