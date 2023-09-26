// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/STULevelItemWidget.h"
#include "STUGameInstance.h"

void USTUMenuWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }
    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }
    InitLevelItems();
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) 
{
    if (Animation != HideAnimation)
        return;
    if (!GetWorld())
        return;

    const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (!STUGameInstance)
        return;

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevel().LevelName);
}

void USTUMenuWidget::OnStartGame() 
{
    PlayAnimation(HideAnimation);

}

void USTUMenuWidget::OnQuitGame() 
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::InitLevelItems() 
{
    const auto STUGameInstance = GetSTUGameInstance();

    if (!STUGameInstance)
        return; 

    checkf(STUGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (!LevelItemsBox)
        return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : STUGameInstance->GetLevelsData())
    {
        auto LevelItemWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget)
            continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);

        
    }
        
    if (STUGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(STUGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(STUGameInstance->GetStartupLevel());
    }
}

void USTUMenuWidget::OnLevelSelected(const FLevelsData& Data) 
{
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance)
        return;

    STUGameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

USTUGameInstance* USTUMenuWidget::GetSTUGameInstance() const
{
    if (!GetWorld())
        return nullptr;
    return GetWorld()->GetGameInstance<USTUGameInstance>();
}
