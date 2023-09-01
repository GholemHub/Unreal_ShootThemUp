// Fill out your copyright notice in the Description page of Project Settings.


#include "Placement/STU_PlacementActorComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
USTU_PlacementActorComponent::USTU_PlacementActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USTU_PlacementActorComponent::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(GetOwner(), UStaticMeshComponent::StaticClass(), TEXT("Cube"));
    if (MeshComponent)
    {
        if (BlankMaterial)
        {
            MeshComponent->SetMaterial(0, BlankMaterial);
            MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
        }
    }
}


// Called every frame
void USTU_PlacementActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USTU_PlacementActorComponent::Plased() 
{
    UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(GetOwner(), UStaticMeshComponent::StaticClass(), TEXT("Cube"));
    if (MeshComponent)
    {
        
        if (DefaultMaterial)
        {
            UE_LOG(LogTemp, Warning, TEXT("HERE is the cube1"))
            MeshComponent->SetMaterial(0, DefaultMaterial);
            MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("HERE is the cube2"))
            MeshComponent->SetMaterial(0, DefaultMaterial);
            MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap); 
            
        }
    }
}

