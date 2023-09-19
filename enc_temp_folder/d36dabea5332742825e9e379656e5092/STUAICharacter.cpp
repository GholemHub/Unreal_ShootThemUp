// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "Components/WidgetComponent.h"
#include "UI/STUHealthBarWidget.h"
#include "Components/STUHealthComponent.h"
#include "BrainComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTUAIController::StaticClass();

    bUseControllerRotationYaw = false;

    // Create and initialize the HealthComponent
    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}


void ASTUAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto STUController = Cast<AAIController>(Controller);
    if (STUController && STUController->BrainComponent)
    {
        STUController->BrainComponent->Cleanup();
    }
}


void ASTUAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<USTUHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthBarWidget)
        return;
    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent(), HealthComponent->IsDead());
}

void ASTUAICharacter::BeginPlay() 
{
    Super::BeginPlay();
    check(HealthWidgetComponent);
}


void ASTUAICharacter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    UpdateHealthWdgetVisibility();
}

void ASTUAICharacter::UpdateHealthWdgetVisibility() 
{
    if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawn())
        return;

    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());

    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}
