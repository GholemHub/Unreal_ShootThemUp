// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STU_PlayerState.h"

void ASTU_PlayerState::LogInfo() 
{
    UE_LOG(LogTemp, Display, TEXT("Team id: %i, Kills: %i, Death: %i"), TeamID, KillNum, DeathNum);
}
