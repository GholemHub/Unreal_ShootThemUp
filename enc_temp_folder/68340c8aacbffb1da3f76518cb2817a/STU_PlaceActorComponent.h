// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "STU_PlaceActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTU_PlaceActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTU_PlaceActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    UPROPERTY(EditAnywhere)
    bool IsBuilding = true;

public:	
	// Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
	void ChangeBuild() { IsBuilding = false; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildMode")
    bool bBuildMode = true;

    UFUNCTION(BlueprintCallable, Category = "BuildMode")
    void SetMyBoolVariable(bool NewValue);

private:
    UPROPERTY(EditAnywhere)
    UMaterialInterface* DefaultMaterial;
    UPROPERTY(EditAnywhere)
    UMaterialInterface* BlankMaterial;
    UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
    TSubclassOf<AActor> ActorToSpawn;
    FVector TraceEnd = FVector(0,0,0);
	AActor* SpawnedActor = nullptr;
    void OnMyActionPressed();

};
