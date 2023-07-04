// Shoot Them Up Game, All Rights Receved


#include "Animations/STUAnimNotify.h"

void USTUAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    OnNotified.Broadcast(MeshComp);
   
}