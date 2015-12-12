// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TitanBotsCharacter.h"
#include "ParticleDefinitions.h"
#include "LightPawn.generated.h"

/**
 * 
 */
UCLASS()
class TITANBOTS_API ALightPawn : public ATitanBotsCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ParticleSpawn, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *ChargeSpawn;

public:

	ALightPawn();

	//@Override
	virtual void SpecialStart() override;

	//@Override
	virtual void SpecialStop() override;

	/** @Override */
	virtual void CooldownEnergy() override;

	/** @Override */
	virtual void EnableEnergyUse() override;

	virtual void RegenerateEnergy() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	/**Disables the charge special for cooldown*/
	void DisableCharge();

	/** Enables the charge special after cooldown*/
	void EnableCharge();

	/** Charge logic for ChargeProj to increase size*/
	void StartCharge();

	/** Spawns the ChargeProj with ChargeAmount size*/
	void EndCharge();

	/** dictates on how large the projectile is*/
	float ChargeAmount;

	FTimerHandle RegenerateHandle;

	FTimerHandle ChargeHandle;

	FTimerHandle CooldownHandle;

	FTimerHandle FireRateHandle;

	/** Gets the ParticleSPawn Object for this Character*/
	FORCEINLINE UParticleSystemComponent *GetChargeSpawn() const{ return ChargeSpawn; }
	
};
