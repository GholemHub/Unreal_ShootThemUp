// Shoot Them Up Game, All Rights Receved


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringAramComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::TurnAround);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);
}

void ASTUBaseCharacter::MoveForward(float Amount) 
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount) 
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::LookUp(float Amount) 
{
    AddControllerPitchInput(Amount);
}

void ASTUBaseCharacter::TurnAround(float Amount) 
{
    AddControllerYawInput(Amount);
}

