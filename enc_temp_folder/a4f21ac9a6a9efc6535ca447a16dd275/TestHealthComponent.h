// Shoot Them Up Game, All Rights Receved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API UTestHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestHealthComponent();
    float GetHealth() const { return Health; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxHealth = 120.0f;

	private:
    float Health = 0.0f;
};
