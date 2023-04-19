// Shoot Them Up Game, All Rights Receved


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STUEquipFinishedAnimNotify.h"
#include "Animations/STUReloadFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    CurrentWeaponIndex = 0;
    InitAnimations();
    EquipWeapon(CurrentWeaponIndex);
    SpawnWeapons();
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }

    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!GetWorld() || !Character)
        return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClasses); 
        if (!Weapon)
            return;
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) 
{
    if (!Weapon || !SceneComponent)
        return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex = 0) 
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Invalid weapon index"));
        return;
    }

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    //Add next to have weapon at the beginig(Have a mistakes)
    //AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName); 
    //if (Weapons.Num() > 0) // weapons is empty at the begining
    //{
        CurrentWeapon = Weapons[WeaponIndex];
        //CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMintage;
        const auto CurrentWeaponData =
            WeaponData.FindByPredicate([&](const FWeaponData& Data) { return Data.WeaponClasses == CurrentWeapon->GetClass(); });

        CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    //}
    EquipAnimInProcess = true;
    PlayAnimMontage(EquipAnimMontage);
    
}

void USTUWeaponComponent::StartFire()
{
    if (!CanFire())
        return;
    CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon() 
{
    if (!CanEquip())
        return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::Reload() 
{
    if (!CanReload())
        return;
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}


void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) 
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;
    Character->PlayAnimMontage(Animation);
}

void USTUWeaponComponent::InitAnimations() 
{
    auto EquipFinishedNotify = FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
    }

    for (auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = FindNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if (!ReloadFinishedNotify)
            continue;
        ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh())
        return;

    EquipAnimInProcess = false;
    //    UE_LOG(LogWeaponComponent, Display, TEXT("Equip finished"));

}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh())
        return;

    ReloadAnimInProgress = false;
    //    UE_LOG(LogWeaponComponent, Display, TEXT("Equip finished"));
}

bool USTUWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProcess;
}

bool USTUWeaponComponent::CanEquip() const
{
    return !EquipAnimInProcess && !ReloadAnimInProgress;
}

bool USTUWeaponComponent::CanReload() const
{
    return CurrentWeapon && !EquipAnimInProcess && !ReloadAnimInProgress;
}


