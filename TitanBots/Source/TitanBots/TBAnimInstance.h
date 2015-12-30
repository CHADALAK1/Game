// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "TBAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TITANBOTS_API UTBAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
    
    class ATitanBotsCharacter *TBCharacter;
	
protected:
    
    UTBAnimInstance();
    
    virtual void NativeInitializeAnimation() override;
    
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    
    // Calculate character direction and speed
    UFUNCTION(BlueprintCallable, Category = "TB Character Animation")
    void SetDirectionAndSpeed(float& OutDirection, float& OutSpeed);
    
public:
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    uint32 bIsInAir : 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    uint32 bIsSpecial : 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    uint32 bIsDead : 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180"))
    float Direction;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (UIMin = "-300", UIMax = "300", ClampMin = "-300", ClampMax = "300"))
    float Speed;
	
};
