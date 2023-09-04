// Shoot Them Up Game, All Rights Receved


#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "Develop/STUCoreTypes.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"
#include "Player/STU_PlayerState.h"

ASTUGameModeBase::ASTUGameModeBase() 
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
    PlayerStateClass = ASTU_PlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay() 
{
    Super::StartPlay();
    CreateTeamsInfo();
    SpawnBots();
    CurrentRound = 1;
    StartRound();
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::SpawnBots() 
{
    if (!GetWorld())
        return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(STUAIController);
    }
}

void ASTUGameModeBase::StartRound() 
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);
}
    
void ASTUGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogTemp, Display, TEXT("Timer :: %i / Round %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("Game over"));
        }
    }
}

void ASTUGameModeBase::ResetPlayers()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}
void ASTUGameModeBase::ResetOnePlayer(AController* Controller) 
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASTUGameModeBase::StartRespawn(AController* Controller) 
{
    const auto RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(Controller);
    if (!RespawnComponent)
        return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

/// <summary>
void ASTUGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld())
        return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        //PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
        SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    UE_LOG(
        LogTemp, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());

    return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller)
        return;

    const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
    if (!Character)
        return;

    const auto PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
    if (!PlayerState)
        return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

/// </summary>

//void ASTUGameModeBase::CreateTeamsInfo() 
//{
//
//    UE_LOG(LogTemp, Warning, TEXT("The material"));
//    if (!GetWorld())
//        return;
//    int32 TeamID = 1;
//    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("The material2"));
//        const auto Controller = It->Get();
//        if (!Controller)
//            continue;
//        const auto PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
//        if (!PlayerState)
//            continue;
//        PlayerState->SetTeamID(TeamID);
//        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
//        SetPlayerColor(Controller);
//        TeamID = TeamID == 1 ? 2 : 1;
//    }
//}

//FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 TeamID) const
//{
//    if (TeamID - 1 < GameData.TeamColors.Num())
//    {
//        UE_LOG(LogTemp, Warning, TEXT("The material3"));
//        return GameData.TeamColors[TeamID - 1];
//    }
//    UE_LOG(LogTemp, Warning, TEXT("No Color for team id: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());
//    return GameData.DefaultTeamColor;
//}

//void ASTUGameModeBase::SetPlayerColor(AController* Controller) 
//{
//    if (!Controller)
//        return;
//    const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
//    if (!Controller)
//        return;
//
//    const auto PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
//
//    if (!PlayerState)
//        return;
//    UE_LOG(LogTemp, Warning, TEXT("The material4"));
//    Character->SetPlayerColor(PlayerState->GetTeamColor());
//}



void ASTUGameModeBase::RespawnRequest(AController* Controller) 
{

}
