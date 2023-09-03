// Fill out your copyright notice in the Description page of Project Settings.


#include "Placement/STU_PlaceActorComponent.h"
#include "Placement/STU_PlacementActorClass.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerInput.h" // Include this header for FInputKeyBinding
#include "Placement/STU_PlacementActorComponent.h"



// Sets default values for this component's properties
USTU_PlaceActorComponent::USTU_PlaceActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USTU_PlaceActorComponent::BeginPlay()
{
	Super::BeginPlay();
    if (bBuildMode)
    {
        SpawnActor();
    }
}

bool bBuildMode_Local = true;

void USTU_PlaceActorComponent::SetMyBoolVariable(bool NewValue)
{
    bBuildMode = NewValue;
    bBuildMode_Local = bBuildMode;
}

// Called every frame
void USTU_PlaceActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
     Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

     if (bBuildMode_Local == true)
     {
     
         APlayerCameraManager* CamManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
         FVector CamLocation = CamManager->GetCameraLocation();
         FVector CamForward = CamManager->GetCameraRotation().Vector();

         FHitResult HitResult;

         bool bHit = UKismetSystemLibrary::LineTraceSingle(this, CamLocation, TraceEnd, UEngineTypes::ConvertToTraceType(ECC_Visibility),
             false, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true);

         if (bHit)
         {
             // Calculate the distance from the camera to the hit location
             float DistanceToHit = FVector::Dist(CamLocation, HitResult.Location);
             // Calculate the spawn location of the actor in front of the camera
             FVector SpawnLocation = CamLocation + (CamForward * (DistanceToHit));
             // Move the spawned actor to the calculated spawn location
             if (SpawnedActor)
             {
                SetupMaterials();
                //SpawnedActor->SetActorLocation(SpawnLocation);
                SnapToGrid(100);
                UStaticMeshComponent* MeshComponent = SpawnedActor->FindComponentByClass<UStaticMeshComponent>();

                if (MeshComponent)
                {
                    MeshComponent->SetMaterial(0, BlankMaterial); // 0 is the index of the material slot to change
                }
             }
         }
     }
     else
     {
         if (SpawnedActor)
         {
            SetupMaterials();
            UStaticMeshComponent* MeshComponent = SpawnedActor->FindComponentByClass<UStaticMeshComponent>();

            if (MeshComponent)
            {  
                MeshComponent->SetMaterial(0, DefaultMaterial); // 0 is the index of the material slot to change
            }
            SpawnActor();
         }

     }
     
}

void USTU_PlaceActorComponent::SnapToGrid(float GridSize)
{
     APlayerCameraManager* CamManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
     FVector CamLocation = CamManager->GetCameraLocation();
     FVector CamForward = CamManager->GetCameraRotation().Vector();
     FHitResult HitResult;
     float DistanceToHit = FVector::Dist(CamLocation, HitResult.Location);
     // Calculate the spawn location of the actor in front of the camera
     FVector SpawnLocation = CamLocation + (CamForward * (DistanceToHit));

     FVector CurrentLocation = SpawnLocation;

     // Snap the X, Y, and Z components to the nearest grid points
     float SnappedX = FMath::RoundToFloat(CurrentLocation.X / GridSize) * GridSize;
     float SnappedY = FMath::RoundToFloat(CurrentLocation.Y / GridSize) * GridSize;
     float SnappedZ = FMath::RoundToFloat(CurrentLocation.Z / GridSize) * GridSize;

     // Create a new FVector with the snapped values
     FVector SnappedLocation(SnappedX, SnappedY, SnappedZ);

     // Set the actor's new location
     if (SpawnedActor)
     {
         SpawnedActor->SetActorLocation(SnappedLocation);
     }
}

void USTU_PlaceActorComponent::OnMyActionPressed()
{
     // This function will be called when the bound key is pressed
     // Implement your desired behavior here
}

void USTU_PlaceActorComponent::SetupMaterials() 
{
     FName ComponentName = FName(TEXT("STU_PlacementActor"));
     TArray<UActorComponent*> ActorComponents;
     if (SpawnedActor)
     {
         SpawnedActor->GetComponents(ActorComponents);

         for (UActorComponent* Component : ActorComponents)
         {
            if (Component->GetFName() == ComponentName)
            {
                // You have found the component, you can now work with it.
                USTU_PlacementActorComponent* PlacementComponent = Cast<USTU_PlacementActorComponent>(Component);
                if (PlacementComponent)
                {
                    // Assuming MaterialToApply is a reference to the material you want to apply
                    DefaultMaterial = PlacementComponent->DefaultMaterial;
                    BlankMaterial = PlacementComponent->BlankMaterial;
                }
                break; // Exit the loop once you find the component.
            }
         }
     }
}

void USTU_PlaceActorComponent::SpawnActor() 
{

     FVector Location(0.0f, 0.0f, 0.0f);
     FRotator Rotation(0.0f, 0.0f, 0.0f);
     SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);
}
