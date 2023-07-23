#include "Weapon/STUBaseWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/MeshComponent.h"
#include "Player/STUBaseCharacter.h"
#include "AI/STUAICharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);
    checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn't be less or equal zero"));
    checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal zero"));
    CurrentAmmo = DefaultAmmo;
}

void ASTUBaseWeapon::StartFire()
{
    FireInProgress = true;
}

void ASTUBaseWeapon::StopFire()
{
    FireInProgress = false;
}

bool ASTUBaseWeapon::IsFiring() const
{
    return FireInProgress;
}

void ASTUBaseWeapon::MakeShot() {}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto STUCharacter = Cast<ACharacter>(GetOwner());
    if (!STUCharacter)
        return false;

    if (STUCharacter->IsPlayerControlled())
    {
        const auto Controller = STUCharacter->GetController<APlayerController>();
        if (!Controller)
            return false;

        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }
    else
    {
        ViewLocation = GetMuzzleWorldLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }

    return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld())
        return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.bReturnPhysicalMaterial = true;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::WhatActorSee(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld())
        return;

    FCollisionQueryParams CollisionParam;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParam);


    // Reset the custom depth rendering for the previous object, if any
    if (MeshComponent)
    {
        MeshComponent->SetRenderCustomDepth(false);
    }

    // If the ray hits an object, check its type and update the custom depth rendering accordingly
    if (HitResult.bBlockingHit)
    {
        
        const auto CurrentActor = HitResult.GetActor();
        if (CurrentActor)
        {
            
            if (CurrentActor->IsA<ASTUBaseCharacter>()) // Replace ABaseBoxActor with the actual class name for your box
            {
                // Set the custom depth to true to change the object's rendering color to green
                UMeshComponent* CurrentMeshComponent = Cast<UMeshComponent>(HitResult.GetComponent());
                if (CurrentMeshComponent)
                {
                    CurrentMeshComponent->SetRenderCustomDepth(true);
                    CurrentMeshComponent->SetCustomDepthStencilValue(1);
                    MeshComponent = CurrentMeshComponent; // Save the current mesh component for future resets
                }
            }
            else  // Replace ABaseSphereActor with the actual class name for your sphere
            {
                // Set the custom depth to true to change the object's rendering color to red
                UMeshComponent* CurrentMeshComponent = Cast<UMeshComponent>(HitResult.GetComponent());
                if (CurrentMeshComponent)
                {
                    CurrentMeshComponent->SetRenderCustomDepth(true);
                    CurrentMeshComponent->SetCustomDepthStencilValue(2);
                    MeshComponent = CurrentMeshComponent; // Save the current mesh component for future resets
                }
            }
        }
    }
}


void ASTUBaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("Clip is empty"));
        return;
    }
    CurrentAmmo.Bullets--;

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

bool ASTUBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}


void ASTUBaseWeapon::ChangeClip()
{
    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips == 0)
        {
            //UE_LOG(LogBaseWeapon, Warning, TEXT("No more clips"));
            return;
        }
        CurrentAmmo.Clips--;
    }
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    // UE_LOG(LogBaseWeapon, Display, TEXT("------ Change Clip ------"));
}

bool ASTUBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

void ASTUBaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

bool ASTUBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips && //
           CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool ASTUBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
    UE_LOG(LogTemp, Error, TEXT("The Reload 123"));

    if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0)
        return false;

    if (IsAmmoEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("The Reload 1"));
        CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnClipEmpty.Broadcast(this);
    }
    else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
    {
        UE_LOG(LogTemp, Error, TEXT("The Reload 2"));
        const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
        if (DefaultAmmo.Clips - NextClipsAmount >= 0)
        {
            CurrentAmmo.Clips = NextClipsAmount;
        }
        else
        {
            CurrentAmmo.Clips = DefaultAmmo.Clips;
            CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("The Reload 3 :: %i/%i"), CurrentAmmo.Clips, CurrentAmmo.Bullets);
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    }

    return true;
}

UNiagaraComponent* ASTUBaseWeapon::SpawnMuzzleFX()
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MazzleFX, //
        WeaponMesh,                                               //
        MuzzleSocketName,                                         //
        FVector::ZeroVector,                                      //
        FRotator::ZeroRotator,                                    //
        EAttachLocation::SnapToTarget, true);
}
