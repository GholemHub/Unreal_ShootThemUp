// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Develop/STUCoreTypes.h"
#include "STUGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
    GENERATED_BODY()
    virtual void DrawHUD() override;
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    virtual void BeginPlay() override;
    UPROPERTY()
    TMap<ESTUMatchState, UUserWidget*> GameWidgets;

private:

    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;


    void DrawCrossHair();
    void OnMatchStateChanged(ESTUMatchState State); 
	
};
