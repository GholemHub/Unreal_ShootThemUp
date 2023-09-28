// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameInstance.h"
#include "Sound/STUSoundFunLib.h"

void USTUGameInstance::ToggleVolume() 
{
    USTUSoundFunLib::ToggleSoundClassVolume(MasterSoundClass);
}
