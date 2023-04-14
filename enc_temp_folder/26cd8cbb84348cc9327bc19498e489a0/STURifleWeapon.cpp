// Shoot Them Up Game, All Rights Receved


#include "Weapon/STURifleWeapon.h"


void ASTURifleWeapon::StartFire()
{
    MakeShot();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTUBaseWeapon::MakeShot, TimeBetweenShots, true);
}

void ASTURifleWeapon::StopFire()
{
    MakeShot();
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
    if (!GetWorld())
        return;

    FVector ViewLocation;
    FRotator ViewRotation;

    FVector TraceStart, TraceEnd;

    if (GetTraceData(TraceStart, TraceEnd))
        return;
    FHitResult HitResult;
    //MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        //UE_LOG(LogBaseWeapon, Warning, TEXT("Fired to the %s"), *HitResult.BoneName.ToString());

        // HitResult.

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;

    //const FVector ShootDirection = ViewRotation.Vector();
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad); // SocketTransform.GetRotation().GetForwardVector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}
