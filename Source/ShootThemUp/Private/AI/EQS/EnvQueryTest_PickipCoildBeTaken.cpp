// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvQueryTest_PickipCoildBeTaken.h"
#include "Pickup/STUBasePickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

UEnvQueryTest_PickipCoildBeTaken::UEnvQueryTest_PickipCoildBeTaken(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickipCoildBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    const auto DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);

    const bool WantsBeTakable = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto PickupActor = Cast<ASTUBasePickup>(ItemActor);
        if (!PickupActor)
            continue;

        const auto CouldBeTaken = PickupActor->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakable);
    }
}
