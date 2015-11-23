// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "LightPawn.h"


ALightPawn::ALightPawn()
{
	GetCharacterMovement()->MaxWalkSpeed = 800.f;
    SetMaxHealth(100);
    SetMaxArmor(200);
}


