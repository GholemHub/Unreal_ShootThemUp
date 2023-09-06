// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player/STUPlayerController.h"

#include "AIController.h"
#include "Develop/STUCoreTypes.h"
#include "STUGameModeBase.generated.h"


/**
 * 
 */

class AAController;

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
    ASTUGameModeBase();
    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void RespawnRequest(AController* Controller);
    UPROPERTY(EditAnywhere)
    bool InBuilding = true;

    void Killed(AController* KillerController, AController* VictimController);

    int32 GetRoundCountDown() { return RoundCountDown; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;
    

private:
    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void StartRespawn(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SetPlayerColor(AController* Controller);

    void LogPlayerInfo();
};
