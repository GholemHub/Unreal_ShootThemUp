// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STU_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTU_PlayerState : public APlayerState
{
	GENERATED_BODY()
public:

	void SetTeamID(int32 ID) { TeamID = ID; }
    int32 GetTeamID() { return TeamID; }

    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
    FLinearColor GetTeamColor() { return TeamColor; }

    void AddKill() { ++KillNum; }
    int32 GetKillsNum() const { return KillNum; }
    void AddDeath() { ++DeathNum; }
    int32 GetDeathNum() const { return DeathNum; }

    void LogInfo();

private :
	int32 TeamID;
    FLinearColor TeamColor;

    int32 KillNum = 0;
    int32 DeathNum = 0;

};