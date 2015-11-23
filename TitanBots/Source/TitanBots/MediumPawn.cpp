// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "MediumPawn.h"


AMediumPawn::AMediumPawn()
{
	SetHealth(200);
	SetArmor(300);
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
}
