// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "WeaponProjectile.h"
#include "TitanBotsCharacter.generated.h"

UCLASS(config=Game)
class ATitanBotsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
    class UBoxComponent *Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ProjSpawn, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *ProjSpawn;

public:
	ATitanBotsCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ID)
	FString CharacterMeshID;

	/**Subclass variable to hold the projectile the Player will fire*/
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AWeaponProjectile> WeapProj;

	/** EnemyPawn Object to dictate what enemy we are fighting and to lock on to(
	(WILL BE A TArray LATER IN THE PROTOTYPE)*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Enemy)
	ATitanBotsCharacter* EnemyPawn;

	/** Bool to tell whether the character is locked onto the enemy*/
	bool bIsLockedOn;

	/** CameraLocation variables for Interloping*/
	float CamLocZ;
	float CamLocY;

	/** Angle variables for Dashing directions*/
	float AngleX;
	float AngleY;

	FTimerHandle DashCooldown;

	/** Plays sound for this character
	* @param Sound  SoundCue to play
	*/
	UAudioComponent *PlaySound(USoundCue *Sound);

	/** Fire sound for this character*/
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireSound;

    /**
     * Get function that returns the PERCENTAGE
     * value for Health
     */
    UFUNCTION(BlueprintCallable, Category = Health)
    float GetHealthPercentage();

	/**
	* Get function that returns the PERCENTAGE
	* value for Armor
	*/
	UFUNCTION(BlueprintCallable, Category = Armor)
	float GetArmorPercentage();

	/**
	* Get function that returns the PERCENTAGE
	* value for Energy
	*/
	UFUNCTION(BlueprintCallable, Category = Energy)
	float GetEnergyPercentage();
    
    /** Adds Health
     * @param Amount  the amount of Health to be added
     */
    void AddHealth(int32 Amount);
    
    /** Decreases health
     * @param Amount  the amount of Health to be decreases
     */
    void DecreaseHealth(int32 Amount);
    
    /** Adds armor
     * @param Amount  the amount of armor to be added
     */
    void AddArmor(int32 Amount);
    
    /** Decreases armor
     * @param Amount  The amount of armor to be depleted
     */
    void DecreaseArmor(int32 Amount);

	/** AddEnergy
	* @param Amount  The amount of Energy to be added
	*/
	void AddEnergy(int32 Amount);

	/** DecreaseEnergy
	* @param Amount  The amount of Energy to be depleted
	*/
	void DecreaseEnergy(int32 Amount);

	/** SetMaxEnergy
	* @param NewMax  Sets the new MaxEnergy amount for the character
	*/
	void SetMaxEnergy(int32 NewMaxEnergy);
    
    /** Sets the new MaxHealth
     * @param NewMaxHealth  The amount set to be for MaxHealth
     */
    void SetMaxHealth(int32 NewMaxHealth);

	/** Sets the amount of Health
	* @param NewHealth the new value for Health
	*/
	void SetHealth(int32 NewHealth);

	/** Sets the amount of armor
	* @param NewArmor  the new value for Armor
	*/
	void SetArmor(int32 NewArmor);

	/** Sets the amount of Energy
	* @param NewEnergy  the new value of Energy
	*/
	void SetEnergy(int32 NewEnergy);

	/**Set Function to turn on or off Special
     *@param Special Turns on or off bIsSpecial
     */
	void SetIsSpecial(bool Special);
    
    /** Sets the new MaxArmor
     * @param NewMaxArmor  The amount set to be for MaxArmor
     */
    void SetMaxArmor(int32 NewMaxArmor);

	/**Sets the bool bIsInvulnerable
     *@param Set Turns on or off bIsInvulnerable
     */
	void SetIsInvulnerable(bool Set);

	/**Sets the bool bIsDead
     *@param Set Turns on or off bIsDead
     */
	void SetIsDead(bool Set);

	/** Sets the bool bCanDash
     *@param Set Turns on or off bCanDash
     */
	void SetCanDash(bool Set);

	/**Sets the bool for bIsCoolingDown
     *@param Set  Turns on or off bIsCoolingDown
     */
	void SetIsCoolingDown(bool Set);

	/**Sets the bool for bCanFireAgain
     *@param Set  Turns on or off bCanFireAgain
     */
	void SetCanFireAgain(bool Set);

	/**Sets the bool for bIsChargeSpecial
     *@param Set turn on or off bIsChargeSpecial
     */
	void SetIsChargeSpecial(bool Set);

	/** Drains the Energy for Character(VIRTUAL FUNCTION)*/
	virtual void DrainEnergy(){}

	/**Regenerates Energy for Character(VIRTUAL FUNCTION)*/
	virtual void RegenerateEnergy(){}

	/**Starts the cooldown for the Energy to replenish*/
	virtual void CooldownEnergy(){}

	/**enables energy to be used and replenishes Energy*/
	virtual void EnableEnergyUse(){}
    
    /** Fires arm cannon/Melee weapon */
	UFUNCTION(BlueprintCallable, Category = Fire)
    void Fire();
    
    /** Stops firing weapon */
	UFUNCTION(BlueprintCallable, Category = Fire)
    void StopFire();

	/**Starts Charge ability for Pawn*/
	virtual void SpecialStart();

	/**Stops Charge ability for Pawn*/
	virtual void SpecialStop();

	/** Exec function that makes the character lock on the enemy*/
	void LockOn();

	/** Logic that holds the rules for locking on the Enemy*/
	void LockOnLogic();

	/** Exec function that makes the character Dash*/
	UFUNCTION(BlueprintCallable, Category = Dash)
	void Dash();

	/** Disables dash for cooling down(PREVENTS BROKEN DASHING*/
	void DisableDash();

	/**Enables dash after cooldown is complete*/
	void EnableDash();

	/** Gets the world for enemies to store for lock on system*/
	UFUNCTION(BlueprintCallable, Category = EnemySearch)
	void DetectEnemy();

	/** Begin Play Native UE4 function*/
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
    
    
private:
    
    /** Health value for the Pawn */
    int32 Health;
    
    /** Armor value for the Pawn */
    int32 Armor;

	/** Energy value for the Pawn(like stamina for the special)*/
	int32 Energy;

	/** Max Energy value for the Pawn*/
	int32 MaxEnergy;
    
    /** int value that hold the Maximum Health */
    int32 MaxHealth;
    
    /** int value that holds the Maximum Armor */
    int32 MaxArmor;

	/** Bool to tell whether the character is currently dashing*/
	bool bIsDashing;

	/** Bool to tell whether the character can dash or not*/
	bool bCanDash;

	/**Bool to tell whether the character's special is on*/
	bool bIsSpecial;

	/** Bool to tell whether the character's invulnerable*/
	bool bIsInvulnerable;

	/** Bool to tell whether the character's Dead*/
	bool bIsDead;

	/** Bool to tell whether the pawn is cooling down on energy use*/
	bool bIsCoolingDown;

	/** Bool that tells whether the LightPawn can fire the Special again*/
	bool bCanFireAgain;

	/** Bool that tells whether the LightPawn is firing the charge special*/
	bool bIsChargeSpecial;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
    
    /** Collision for the Collision Box */
    UFUNCTION()
    void OnEnterCollision(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
    
    /**              ACCESSORS           */
    
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    /** Returns Collision subobject **/
    FORCEINLINE class UBoxComponent* GetCollision() const { return Collision; }
	/** Returns ProjSPawn subobject */
	FORCEINLINE class UBoxComponent* GetProjSpawn() const { return ProjSpawn; }
    /** Gets the Health Value for this Character */
    FORCEINLINE int32 GetHealth() const { return Health;}
    /** Gets the Armor Value for this Character */
    FORCEINLINE int32 GetArmor() const { return Armor; }
    /** Gets the MaxHealth Value for this Character */
    FORCEINLINE int32 GetMaxHealth() const { return MaxHealth; }
    /** Gets the MaxArmor Value for this Character */
    FORCEINLINE int32 GetMaxArmor() const { return MaxArmor; }
	/** Gets the Energy Value for this Character*/
	FORCEINLINE int32 GetEnergy() const { return Energy; }
	/** Gets the MaxEnergy Value for this Character*/
	FORCEINLINE int32 GetMaxEnergy() const { return MaxEnergy; }
	/**Gets the bool for bCanDash for this Character*/
	FORCEINLINE bool CanDash() const { return bCanDash; }
	/**Gets the bool for bIsDashing for this Character*/
	FORCEINLINE bool IsDashing() const { return bIsDashing; }
	/** Gets the bool for bIsInvulnerable for this character*/
	FORCEINLINE bool IsInvulnerable() const { return bIsInvulnerable; }
	/** Gets the bool for bIsDead for this character*/
    FORCEINLINE bool IsDead() const { return bIsDead; }
	/**Get function for the bIsSpecial bool*/
	FORCEINLINE bool IsSpecial() const { return bIsSpecial; }
	/**Gets the bIsCoolingDown bool that is in the Medium Character*/
	FORCEINLINE bool IsCoolingDown() const { return bIsCoolingDown; }
	/** Gets the bCanFireAgain bool that is in Light Character*/
	FORCEINLINE bool CanFireAgain() const { return bCanFireAgain; }
	/** Gets the bIsChargeSpecial bool (FOR THE LIGHT CHARACTER*/
	FORCEINLINE bool IsChargeSpecial() const { return bIsChargeSpecial; }

};

