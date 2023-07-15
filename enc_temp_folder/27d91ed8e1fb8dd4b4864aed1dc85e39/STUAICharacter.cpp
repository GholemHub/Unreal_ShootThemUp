// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "BrainComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // Constructor implementation
}

void ASTUAICharacter::OnDeath() 
{
    Super::OnDeath();

    const auto STUController = Cast<ASTUAIController>(Controller);

    if (STUController && STUController->BrainComponent)
    {
        STUController->BrainComponent->Cleanup();
    }
}
