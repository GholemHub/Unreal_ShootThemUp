// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound/STUSoundFunLib.h"
#include "Sound/SoundClass.h"


void USTUSoundFunLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume) 
{
    if (!SoundClass)
        return;
    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.f, 1.f);
    UE_LOG(LogTemp, Display, TEXT("SoundClass was changed %s = %f"), *SoundClass->GetName(), SoundClass->Properties.Volume);
}

void USTUSoundFunLib::ToggleSoundClassVolume(USoundClass* SoundClass) 
{
    if (!SoundClass)
        return;
    const auto NextVolume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f;
    SetSoundClassVolume(SoundClass, NextVolume);
}
