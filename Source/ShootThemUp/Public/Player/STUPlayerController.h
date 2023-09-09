// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
};
