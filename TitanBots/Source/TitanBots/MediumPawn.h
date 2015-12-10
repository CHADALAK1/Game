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

	/** Bool to tell whether the pawn is cooling down on energy use*/
	bool bIsCoolingDown;

public:
	AMediumPawn();

	//@Override
	virtual void SpecialStart() override;

	//@Override
	virtual void SpecialStop() override;
	
	virtual void Tick(float DeltaSeconds) override;

	/**Sets the bool for bIsCoolingDown*/
	void SetIsCoolingDown(bool Set);

	/**@Override
	* Drains the Energy for the Medium Pawn
	*/
	virtual void DrainEnergy() override;

	/**@Override
	* Regenerates Energy for Medium Pawn
	*/
	virtual void RegenerateEnergy() override;

	/**Starts the cooldown for the Energy to replenish*/
	void CooldownEnergy();

	/**enables energy to be used and replenishes Energy*/
	void EnableEnergyUse();

	/**Timer Handle for the Cooldown*/
	FTimerHandle CooldownHandle;

	/**Timer Handle for the Drain*/
	FTimerHandle DrainHandle;

	/**Timer Handle for the Regenerate*/
	FTimerHandle RegenerateHandle;

	/**Gets the Shield Object that is in the Medium Pawn*/
	FORCEINLINE UBoxComponent *GetShield() const { return Shield; }
	/**Gets the bIsCoolingDown bool that is in the Medium Character*/
	FORCEINLINE bool IsCoolingDown() const { return bIsCoolingDown; }
	
};
