// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Player/STU_PlayerState.h"
#include "STUUtils.h"
#include "UI/STUUserStatRowWidget.h"
#include "Kismet/GameplayStatics.h"

void USTUGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        if (const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
        }
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
    }
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State) {
    if (State == ESTUMatchState::GameOver)
    {
        UpdatePlayersStat();
    }
}

void USTUGameOverWidget::UpdatePlayersStat() 
{
    if (!GetWorld() || !PlayerStatBox)
        return;

    PlayerStatBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;
      
        const auto PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;
       
        const auto PlayerStatWidget = CreateWidget<USTUUserStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatWidget)
            continue;

        PlayerStatWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathNum()));
        PlayerStatWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

        PlayerStatBox->AddChild(PlayerStatWidget);
    }
}

void USTUGameOverWidget::OnResetLevel() 
{
    UE_LOG(LogTemp, Error, TEXT("RESET LEVEl"));
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}


