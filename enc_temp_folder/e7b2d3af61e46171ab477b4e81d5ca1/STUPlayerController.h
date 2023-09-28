// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Develop/STUCoreTypes.h"
#include "STUPlayerController.generated.h"

/**
 * 
 */
class USTURespawnComponent;
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    ASTUPlayerController();
    virtual void OnPossess(APawn* InPawn) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    USTURespawnComponent* RespawnComponent;
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

private:
    void OnPaseGame();
    void OnMatchStateChanged(ESTUMatchState State);
};
