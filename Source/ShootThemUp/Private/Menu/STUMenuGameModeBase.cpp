// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/STUMenuGameModeBase.h"
#include "Menu/STUManuPlayerController.h"
#include "Menu/UI/STUMenuHUD.h"

ASTUMenuGameModeBase::ASTUMenuGameModeBase()
{
    PlayerControllerClass = ASTUManuPlayerController::StaticClass();
    HUDClass = ASTUMenuHUD::StaticClass();
}
