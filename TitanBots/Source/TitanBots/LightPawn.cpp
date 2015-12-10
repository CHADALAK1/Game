// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "LightPawn.h"


ALightPawn::ALightPawn()
{
	ChargeSpawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ChargeSpawn"));
	ChargeSpawn->AttachTo(GetProjSpawn());

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
    SetMaxHealth(100);
    SetMaxArmor(200);
}

void ALightPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsSpecial())
	{

	}
}

void ALightPawn::SpecialStart()
{
	Super::SpecialStart();
}

void ALightPawn::SpecialStop()
{
	Super::SpecialStop();
}


