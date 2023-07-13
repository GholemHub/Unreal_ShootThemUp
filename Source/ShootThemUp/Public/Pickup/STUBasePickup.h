// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

	ASTUBasePickup();
    bool CouldBeTaken() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    FTimerHandle RespawnTimerHandle;
	float RotationYaw = 0.0f;
    virtual bool GivePickupTo(APawn* PlayerPawn);
    void PickUpWasTaken();
    void Respawn();

	void GenerateRotationYaw();
};
