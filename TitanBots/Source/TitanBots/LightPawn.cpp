// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "LightPawn.h"


ALightPawn::ALightPawn()
{
	ChargeSpawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ChargeSpawn"));
	ChargeSpawn->AttachTo(GetProjSpawn());
	ChargeSpawn->SetRelativeScale3D(FVector(0, 0, 0));

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
    SetMaxHealth(100);
	SetHealth(100);
    SetMaxArmor(200);
	SetArmor(200);
	SetMaxEnergy(500);
	SetEnergy(500);


	ChargeAmount = 0.f;
}

void ALightPawn::BeginPlay()
{
	ChargeSpawn->Deactivate();
}

void ALightPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ALightPawn::SpecialStart()
{
	Super::SpecialStart();
	if (CanFireAgain())
	{
		if (!IsCoolingDown())
		{
			SetIsSpecial(true);
			SetIsChargeSpecial(true);
			GetChargeSpawn()->Activate();
			GetWorld()->GetTimerManager().ClearTimer(RegenerateHandle);
			GetWorld()->GetTimerManager().SetTimer(ChargeHandle, this, &ALightPawn::StartCharge, 0.05f, true);
		}
	}
}

void ALightPawn::SpecialStop()
{
	Super::SpecialStop();
	if (CanFireAgain())
	{
		if (!IsCoolingDown())
		{
			SetIsSpecial(false);
			SetIsChargeSpecial(false);
			GetWorld()->GetTimerManager().ClearTimer(ChargeHandle);
			EndCharge();
		}
	}
}

void ALightPawn::StartCharge()
{
	if (GetEnergy() > 0)
	{
		if (ChargeAmount < 3.f && GetEnergy() > 0)
		{
			ChargeAmount += 0.1f;
			GetChargeSpawn()->SetRelativeScale3D(FVector(ChargeAmount, ChargeAmount, ChargeAmount));
			DecreaseEnergy(5);
		}
		else
		{
			ChargeAmount = 3.f;
		}
	}
}

void ALightPawn::EndCharge()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;
	GetChargeSpawn()->SetRelativeScale3D(FVector(0, 0, 0));
	AWeaponProjectile *Proj = GetWorld()->SpawnActor<AWeaponProjectile>(WeapProj, GetProjSpawn()->GetComponentLocation(), GetFollowCamera()->GetForwardVector().Rotation(), SpawnParams);
	if (Proj)
	{
		Proj->GetAuraParticle()->SetRelativeScale3D(FVector(ChargeAmount, ChargeAmount, ChargeAmount));
	}
	ChargeAmount = 0.f;
	GetChargeSpawn()->Deactivate();
	DisableCharge();
	if (GetEnergy() > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(RegenerateHandle, this, &ALightPawn::RegenerateEnergy, 0.3f, true);
	}
	else
	{
		CooldownEnergy();
	}
}

void ALightPawn::DisableCharge()
{
	SetCanFireAgain(false);
	GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &ALightPawn::EnableCharge, 3.0f, false);
}

void ALightPawn::EnableCharge()
{
	SetCanFireAgain(true);
	GetWorld()->GetTimerManager().ClearTimer(FireRateHandle);
}

void ALightPawn::RegenerateEnergy()
{
	Super::RegenerateEnergy();
	if (GetEnergy() < GetMaxEnergy())
	{
		AddEnergy(1);
	}
}

void ALightPawn::CooldownEnergy()
{
	Super::CooldownEnergy();
	SetIsCoolingDown(true);
	GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &ALightPawn::EnableEnergyUse, 8.0f, false);
}

void ALightPawn::EnableEnergyUse()
{
	Super::EnableEnergyUse();
	SetIsCoolingDown(false);
	SetEnergy(GetMaxEnergy());
	GetWorld()->GetTimerManager().ClearTimer(CooldownHandle);
}


