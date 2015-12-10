// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "MediumPawn.h"


AMediumPawn::AMediumPawn()
{
	Shield = CreateDefaultSubobject<UBoxComponent>(TEXT("Shield"));
	Shield->AttachTo(RootComponent);

	SetMaxHealth(200);
	SetHealth(200);
	SetMaxArmor(300);
	SetArmor(300);
	SetMaxEnergy(500);
	SetEnergy(500);
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
}

void AMediumPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMediumPawn::SetIsCoolingDown(bool Set)
{
	bIsCoolingDown = Set;
}

void AMediumPawn::SpecialStart()
{
	Super::SpecialStart();
	if (!IsCoolingDown())
	{
		SetIsInvulnerable(true);
		GetShield()->SetCollisionProfileName("BlockAllDynamic");
		GetWorld()->GetTimerManager().ClearTimer(RegenerateHandle);
		GetWorld()->GetTimerManager().SetTimer(DrainHandle, this, &AMediumPawn::DrainEnergy, 0.01f, true);
	}
}

void AMediumPawn::SpecialStop()
{
	Super::SpecialStop();
	if (!IsCoolingDown())
	{
		SetIsInvulnerable(false);
		GetShield()->SetCollisionProfileName("NoCollision");
		GetWorld()->GetTimerManager().ClearTimer(DrainHandle);
		GetWorld()->GetTimerManager().SetTimer(RegenerateHandle, this, &AMediumPawn::RegenerateEnergy, 0.05f, true);
	}
}

void AMediumPawn::DrainEnergy()
{
	Super::DrainEnergy();
	if (GetEnergy() > 1)
	{
		DecreaseEnergy(1);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(DrainHandle);
		CooldownEnergy();
	}
}

void AMediumPawn::RegenerateEnergy()
{
	Super::RegenerateEnergy();
	if (GetEnergy() < GetMaxEnergy())
	{
		AddEnergy(1);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenerateHandle);
	}
}

void AMediumPawn::CooldownEnergy()
{
	SetIsCoolingDown(true);
	GetShield()->SetCollisionProfileName("NoCollision");
	SetIsInvulnerable(false);
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &AMediumPawn::EnableEnergyUse, 8.0f, false);
}

void AMediumPawn::EnableEnergyUse()
{
	SetIsCoolingDown(false);
	SetEnergy(GetMaxEnergy());
}
