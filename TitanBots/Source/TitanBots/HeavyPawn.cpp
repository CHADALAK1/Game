// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "HeavyPawn.h"


AHeavyPawn::AHeavyPawn()
{
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
    SetMaxArmor(300);
    SetMaxHealth(200);
}

