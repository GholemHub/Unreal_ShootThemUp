// Shoot Them Up Game, All Rights Receved


#include "Components/STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"
#include "Components/STUCharacterMovementComponent.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());

    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
