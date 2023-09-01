// Shoot Them Up Game, All Rights Receved


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Logging/LogMacros.h"
#include "Components/STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Placement/STU_PlacementActorComponent.h"
#include "Placement/STU_PlaceActorComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
    
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringAramComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    STUHealth = CreateDefaultSubobject<USTUHealthComponent>("STUHealthComponent");
    TestRender = CreateDefaultSubobject<UTextRenderComponent>("TestRender");
    TestRender->SetupAttachment(GetRootComponent());

    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
    PlacementComponent = CreateDefaultSubobject<USTU_PlacementActorComponent>("PlacementComponent");
    PlaceActorComponent = CreateDefaultSubobject<USTU_PlaceActorComponent>("PlaceActorComponent");


}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    check(STUHealth);
    check(TestRender);
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

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &USTUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Released, WeaponComponent, &USTUWeaponComponent::Reload);

    PlayerInputComponent->BindAction("Placement", IE_Pressed, this, &ASTUBaseCharacter::OnPlacementPressed);
}

void ASTUBaseCharacter::OnPlacementPressed()
{
    if (PlaceActorComponent)
    {
        PlaceActorComponent->ChangeBuild();
        PlaceActorComponent->SetMyBoolVariable(bIsBuilding);
        bIsBuilding = !bIsBuilding;

        UE_LOG(LogTemp, Error, TEXT("Here!"))
    }
}

void ASTUBaseCharacter::OnStartFire()
{
    if (IsRunning())
        return;
    WeaponComponent->StartFire();
}

bool ASTUBaseCharacter::IsRunning() const
{
    
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
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

void ASTUBaseCharacter::MoveForward(float Amount) 
{
    //PlaceActorComponent->SetMyBoolVariable(true);
    IsMovingForward = Amount > 0.0f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount) 
{
    if (Amount == 0.0f)
        return; 
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::OnStartRunning() 
{
    WantsToRun = true;
}

void ASTUBaseCharacter::OnStopRunning() 
{
    WantsToRun = false;
}

void ASTUBaseCharacter::OnDeath() 
{
    //PlayAnimMontage(DeathAnimMintage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void ASTUBaseCharacter::OnHealthChanged(float Health, float HealthDelta ) 
{
    TestRender->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
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



