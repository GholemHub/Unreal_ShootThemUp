#pragma once

#include "Player/STU_PlayerState.h"

class STUUtils
{
public:
    template <typename T> static T* GetSTUPlayerComponent(AActor* SomeActor)
    {
        if (!SomeActor)
            return nullptr;

        const auto Component = SomeActor->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }

    static FText TextFromInt(int32 Number) { return FText::FromString(FString::FromInt(Number)); }

    bool static AreEnemis(AController* Controller1, AController* Controller2) { 
        if (!Controller1 || !Controller2 || Controller1 == Controller2)
            return false;
        const auto PlayerState1 = Cast<ASTU_PlayerState>(Controller1->PlayerState);
        const auto PlayerState2 = Cast<ASTU_PlayerState>(Controller2->PlayerState);

        return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
    }
};