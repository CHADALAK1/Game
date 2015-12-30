// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "TBAnimInstance.h"




UTBAnimInstance:: UTBAnimInstance()
{
    bIsInAir = false;
    Speed = 0.f;
    Direction = 0.f;
}

void UTBAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    TBCharacter = Cast<ATitanBotsCharacter>(TryGetPawnOwner());
}

void UTBAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if(!TBCharacter) return;
    
    bIsInAir = TBCharacter->GetMovementComponent()->IsFalling();
    bIsDead = TBCharacter->IsDead();
    bIsSpecial = TBCharacter->IsSpecial();
    SetDirectionAndSpeed(Direction, Speed);
}

void UTBAnimInstance::SetDirectionAndSpeed(float& OutDirection, float& OutSpeed)
{
    const FVector Velocity = TBCharacter->GetVelocity();
    const FRotator Rotation = TBCharacter->GetActorRotation();
    
    OutDirection = CalculateDirection(Velocity, Rotation);
    OutSpeed = Velocity.Size();
}