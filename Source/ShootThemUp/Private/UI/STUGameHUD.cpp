// Shoot Them Up Game, All Rights Receved


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "STUGameModeBase.h"
#include "Blueprint/UserWidget.h"

void ASTUGameHUD::DrawHUD() 
{
    Super::DrawHUD();
    //DrawCrossHair();
}

void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();

 
    GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget)
            continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
        }
    }
}

void ASTUGameHUD::DrawCrossHair()
{

    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColir = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColir, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColir, LineThickness);
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State) 
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }

    UE_LOG(LogTemp, Warning, TEXT("Mode state: %s"), *UEnum::GetValueAsString(State));
}
