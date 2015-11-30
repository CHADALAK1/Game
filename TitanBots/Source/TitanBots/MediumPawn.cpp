// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "MediumPawn.h"


AMediumPawn::AMediumPawn()
{
	SetMaxHealth(200);
	SetHealth(200);
	SetMaxArmor(300);
	SetArmor(300);
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
}
