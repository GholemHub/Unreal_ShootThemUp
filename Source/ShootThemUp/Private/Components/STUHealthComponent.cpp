#include "Components/STUHealthComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TimerManager.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShakeBase.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}



bool USTUHealthComponent::TryToHeal(float HealthPoint)
{

    if (Health != 0 && Health != MaxHealth)
    {
        SetHealth(Health + HealthPoint);
        //UE_LOG(LogHealthComponent, Error, TEXT("Added health"));   
        return true;
    }
    else
    {
       // UE_LOG(LogHealthComponent, Error, TEXT("Not Added health"));   
        return false;
    }
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    SetHealth(MaxHealth);

    check(MaxHealth > 0);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &USTUHealthComponent::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USTUHealthComponent::OnTakeRadialDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    UE_LOG(LogTemp, Error, TEXT("Any %f"), Damage)
}

void USTUHealthComponent::HealUpdate() {
    SetHealth(Health + HealModifier);
    
    if (Health==MaxHealth && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }

}

void USTUHealthComponent::OutlineUpdate() 
{
    AActor* ComponentOwner = GetOwner();
    ComponentOwner->FindComponentByClass<UMeshComponent>();

    const auto Actor = ComponentOwner->FindComponentByClass<UMeshComponent>();

    Actor->SetRenderCustomDepth(false);

    GetWorld()->GetTimerManager().ClearTimer(OutlineTimerHandle);
    
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDela = NextHealth - Health;

    Health = NextHealth;
    //UE_LOG(LogHealthComponent, Error, TEXT("HERE is %f"), Health);
    OnHealthChanged.Broadcast(Health, HealthDela);
}

void USTUHealthComponent::PlayCameraShake() 
{
    if(IsDead()) return;
    const auto Player = Cast<APawn>(GetOwner());
    if (!Player)
        return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager)
        return; 
    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USTUHealthComponent::DamageOutline(AActor* DamagedActor)
{
    if (const auto Actor = DamagedActor->FindComponentByClass<UMeshComponent>())
    {
        Actor->SetRenderCustomDepth(true);
        Actor->SetCustomDepthStencilValue(1);

        GetWorld()->GetTimerManager().SetTimer(OutlineTimerHandle, this, &USTUHealthComponent::OutlineUpdate, 0.3f, true);
    }
}

void USTUHealthComponent::Killed(AController* KillerController) 
{
    const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode)
        return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictimController);
}

void USTUHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy) 
{
    DamageOutline(InstigatedBy);

    if (Damage <= 0.0f || IsDead() || !GetWorld())
        return;
    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
    PlayCameraShake();
}

float USTUHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
    const auto Character = Cast<ACharacter>(DamagedActor);
    if (!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName))
        return 1.0f;

    const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();

    if (!PhysMaterial || !DamageModifiers.Contains(PhysMaterial))
        return 1.f;
    
    return DamageModifiers[PhysMaterial];
     
}

void USTUHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
    UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
    const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
    UE_LOG(LogTemp, Error, TEXT("Point %f,Final Damage::%f, bone %s"), Damage, FinalDamage, *BoneName.ToString())
    ApplyDamage(FinalDamage, InstigatedBy);
  

}

void USTUHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin,
    const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
    UE_LOG(LogTemp, Error, TEXT("Radial %f"), Damage) 
    ApplyDamage(Damage, InstigatedBy);
}