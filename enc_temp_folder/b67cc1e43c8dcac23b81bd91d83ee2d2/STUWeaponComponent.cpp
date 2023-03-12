// Shoot Them Up Game, All Rights Receved


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
    if (!GetWorld())
        return;
    
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;
    const auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
        
    if (!Weapon)
        return; 
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
    
}


