// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TitanBotsCharacter.h"
#include "MediumPawn.generated.h"

/**
 * 
 */
UCLASS()
class TITANBOTS_API AMediumPawn : public ATitanBotsCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Shield, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *Shield;

private:

public:
	AMediumPawn();

	//@Override
	virtual void SpecialStart() override;

	//@Override
	virtual void SpecialStop() override;
	
	virtual void Tick(float DeltaSeconds) override;

	/**@Override
	* Drains the Energy for the Medium Pawn
	*/
	virtual void DrainEnergy() override;

	/**@Override
	* Regenerates Energy for Medium Pawn
	*/
	virtual void RegenerateEnergy() override;

	/** @Override */
	virtual void CooldownEnergy() override;

	/** @Override */
	virtual void EnableEnergyUse() override;

	/**Timer Handle for the Cooldown*/
	FTimerHandle CooldownHandle;

	/**Timer Handle for the Drain*/
	FTimerHandle DrainHandle;

	/**Timer Handle for the Regenerate*/
	FTimerHandle RegenerateHandle;

	/**Gets the Shield Object that is in the Medium Pawn*/
	FORCEINLINE UBoxComponent *GetShield() const { return Shield; }
	
};
