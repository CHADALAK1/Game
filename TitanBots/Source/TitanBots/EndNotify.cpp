// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "TitanBotsCharacter.h"
#include "EndNotify.h"



UEndNotify::UEndNotify()
{
    
}

void UEndNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    ATitanBotsCharacter *Char = Cast<ATitanBotsCharacter>(MeshComp->GetOwner());
    if(Char)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "HELLO I NOTIFYED");
    }
}
