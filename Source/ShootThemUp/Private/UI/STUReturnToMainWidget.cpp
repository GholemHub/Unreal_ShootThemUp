// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUReturnToMainWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USTUReturnToMainWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (RetrunToMenu)
    {
        RetrunToMenu->OnClicked.AddDynamic(this, &USTUReturnToMainWidget::OnReturnToMenu);
    }
}

void USTUReturnToMainWidget::OnReturnToMenu() 
{
    const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (!STUGameInstance)
        return;
    if (STUGameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogTemp, Error, TEXT("World name is NUNE"));
        return;
    }

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetMenuLevelName());
}
