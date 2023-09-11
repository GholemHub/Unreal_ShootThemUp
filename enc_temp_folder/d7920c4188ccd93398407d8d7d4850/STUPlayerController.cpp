#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "GameFramework/GameModeBase.h"


ASTUPlayerController::ASTUPlayerController() 
{
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::OnPossess(APawn* InPawn) 
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}

void ASTUPlayerController::SetupInputComponent() 
{
    Super::SetupInputComponent();

    if (!InputComponent)
        return;
    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPaseGame);
}

void ASTUPlayerController::BeginPlay() {}

void ASTUPlayerController::OnPaseGame() 
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}


