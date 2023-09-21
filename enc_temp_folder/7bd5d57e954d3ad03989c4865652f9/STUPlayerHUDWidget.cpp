// Shoot Them Up Game, All Rights Receved


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/ProgressBar.h"
#include "Player/STU_PlayerState.h"
#include "Player/STUPlayerState.h"
#include "STUGameModeBase.h"

#include "STUUtils.h"

float USTUPlayerHUDWidget::GetHealthPervent() const
{
    
    const auto HealthComponent = GetHealthComponent();
    if (!HealthComponent)
        return 0.0f;
    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return false;

    const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
    if (!WeaponComponent)
        return false;
    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIAmmoData(FAmmoData& AmmoUIData) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return false;

    const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
    if (!WeaponComponent)
    {
        return false;
    }

    return WeaponComponent->GetCurrentWeaponAmmoUIData(AmmoUIData);
}

int32 USTUPlayerHUDWidget::GetKillsUIAmmoData() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return 0;

   const auto PlayerController = Player->GetController();
    if (!PlayerController)
        return 0;
   const auto PlayerState = Cast<ASTU_PlayerState>(PlayerController->PlayerState);
  
   return PlayerState->GetKillsNum();
}

int32 USTUPlayerHUDWidget::GetKillsNum() const
{
   const auto Controller = GetOwningPlayerPawn();
   if (!Controller)
        return 0;

   const auto PlayerState = Cast<ASTU_PlayerState>(Controller->GetPlayerState());
   return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString USTUPlayerHUDWidget::GetRoundUIData() const
{
   const auto Player = GetOwningPlayerPawn();
   if (!Player)
        return "";

   const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

   return GameMode->GetRoundData();
}

float USTUPlayerHUDWidget::GetRoundTimerUIAmmoData() const
{
   const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
   

   return GameMode->GetRoundCountDown();
}


bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = GetHealthComponent();

    return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

void USTUPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
   
}

USTUHealthComponent* USTUPlayerHUDWidget::GetHealthComponent() const
{

    const auto Player = GetOwningPlayerPawn();
    if (!Player)
        return nullptr;

    const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
    const auto HealthComponent = Cast<USTUHealthComponent>(Component);
    return HealthComponent;
}

void USTUPlayerHUDWidget::OnHealthCanged(float Health, float HealthDelta) 
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
    }
    UpdateHealthBar();
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* NewPawn) 
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthCanged);
    }
    UpdateHealthBar();
}

void USTUPlayerHUDWidget::UpdateHealthBar() 
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPervent() > PercentVisibilityThreshold ? GoodColor : BadColor);
    }
}
