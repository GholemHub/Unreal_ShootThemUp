// Shoot Them Up Game, All Rights Receved


#include "Weapon/STULouncherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASTULouncherWeapon::StartFire() {
    MakeShot();
}


void ASTULouncherWeapon::MakeShot()
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
    // Set pr params

    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
