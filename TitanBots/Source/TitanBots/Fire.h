// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "Fire.generated.h"

/**
 * 
 */
UCLASS()
class TITANBOTS_API UFire : public UAnimNotify
{
	GENERATED_BODY()
	
public:
    UFire();
    
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase *Animation) override;
	
	
};
