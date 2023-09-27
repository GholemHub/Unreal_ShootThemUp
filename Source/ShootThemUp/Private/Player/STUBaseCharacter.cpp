// Shoot Them Up Game, All Rights Receved


#include "Player/STUBaseCharacter.h"

#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Logging/LogMacros.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"


DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

    STUHealth = CreateDefaultSubobject<USTUHealthComponent>("STUHealthComponent");
    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
 

}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    check(STUHealth);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(STUHealth->GetHealth(), 0.0f);
    STUHealth->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    STUHealth->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTUBaseCharacter::OnStartFire()
{
 
    WeaponComponent->StartFire();
}

bool ASTUBaseCharacter::IsRunning() const
{
    return false;
}

float ASTUBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();//вирахували нормалі нашого вектору
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));//скалярний добуток вектор нормалі та беремо з нього аркосінус
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);//Вектор між векторами -- після вираховуємо артогональний вектор
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z); // беремо наші градуси та перемножуємо на знак координати Z
}

void ASTUBaseCharacter::SetPlayerColor(const FLinearColor& Color) 
{
    const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInst)
        return;
    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}


void ASTUBaseCharacter::OnDeath() 
{
    //PlayAnimMontage(DeathAnimMintage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);
    
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void ASTUBaseCharacter::OnHealthChanged(float Health, float HealthDelta ) 
{
    
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit) 
{
    const auto FallVelocityZ = GetCharacterMovement()->Velocity.Z;

    UE_LOG(BaseCharacterLog, Warning, TEXT("On lended %f"), FallVelocityZ);

    if (-FallVelocityZ < LandedVectorVelocity.X)
        return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedVectorVelocity, LandedDamage, -FallVelocityZ);
    UE_LOG(BaseCharacterLog, Warning, TEXT("FinalDamage %f"), FinalDamage);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);


}



