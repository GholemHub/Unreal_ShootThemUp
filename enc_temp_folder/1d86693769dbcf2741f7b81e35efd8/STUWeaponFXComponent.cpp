// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


// Sets default values for this component's properties
USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
    auto ImpactData = DefaultImpactData;

	if (Hit.PhysMaterial.IsValid())
	{
        const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
            ImpactData = ImpactDataMap[PhysMat];
		}
	}


	//Niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	//Decal
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), //
        ImpactData.DecalData.Material, ImpactData.DecalData.Size, Hit.ImpactPoint, (Hit.ImpactNormal * -1.0f).Rotation());

	if (DecalComponent)
	{
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}
}
