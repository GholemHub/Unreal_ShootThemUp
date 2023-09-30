// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Develop/STUCoreTypes.h"
#include "STUGameInstance.generated.h"

class USoundClass;

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    FLevelsData GetStartupLevel() const { return StartupLevel; }
    void SetStartupLevel(const FLevelsData& Data) { StartupLevel = Data; }

    TArray<FLevelsData> GetLevelsData() const { return LevelsData; }

    FName GetMenuLevelName() { return MenuLevelName; }

    void ToggleVolume();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TArray<FLevelsData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;

private:
    FLevelsData StartupLevel;

};
