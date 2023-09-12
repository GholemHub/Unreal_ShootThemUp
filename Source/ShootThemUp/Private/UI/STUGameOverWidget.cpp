// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Components/VerticalBox.h"
#include "Player/STU_PlayerState.h"
#include "STUUtils.h"
#include "UI/STUUserStatRowWidget.h"

bool USTUGameOverWidget::Initialize()
{
    const auto Initialize = Super::Initialize();
    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
        }
    }
    return Initialize;
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
            return;

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


