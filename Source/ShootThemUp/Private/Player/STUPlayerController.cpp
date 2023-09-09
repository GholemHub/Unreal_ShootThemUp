// Shoot Them Up Game, All Rights Receved


#include "Components/STURespawnComponent.h"
#include "Player/STUPlayerController.h"

ASTUPlayerController::ASTUPlayerController() 
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::OnPossess(APawn* InPawn) 
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}


