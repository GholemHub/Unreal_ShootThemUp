// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/STUManuPlayerController.h"
#include "STUGameInstance.h"

void ASTUManuPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
