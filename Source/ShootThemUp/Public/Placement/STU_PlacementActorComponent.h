// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "STU_PlacementActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTU_PlacementActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTU_PlacementActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
    


public:	
	UPROPERTY(EditAnywhere)
    UMaterialInterface* BlankMaterial;
	UPROPERTY(EditAnywhere)
    UMaterialInterface* DefaultMaterial;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void Plased();

private:
    //UPROPERTY(EditAnywhere)
    //UStaticMeshComponent* StaticMeshComponent;
};
