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
	ATitanBotsCharacter* EnemyPawn;

	/** Bool to tell whether the character is locked onto the enemy*/
	bool bIsLockedOn;

	/** CameraLocation variables for Interloping*/
	float CamLocZ;
	float CamLocY;

	/** Angle variables for Dashing directions*/
	float AngleX;
	float AngleY;


    
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
    
    /** Sets the amount of Health
     * @param NewHealth the new value for Health
     */
    void SetHealth(int32 NewHealth);
    
    /** Sets the amount of armor
     * @param NewArmor  the new value for Armor
     */
    void SetArmor(int32 NewArmor);
    
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
    
    /** Sets the new MaxHealth
     * @param NewMaxHealth  The amount set to be for MaxHealth
     */
    void SetMaxHealth(int32 NewMaxHealth);
    
    /** Sets the new MaxArmor
     * @param NewMaxArmor  The amount set to be for MaxArmor
     */
    void SetMaxArmor(int32 NewMaxArmor);
    
    /** Fires arm cannon/Melee weapon */
	UFUNCTION(BlueprintCallable, Category = Fire)
    void Fire();
    
    /** Stops firing weapon */
	UFUNCTION(BlueprintCallable, Category = Fire)
    void StopFire();

	/** Exec function that makes the character lock on the enemy*/
	void LockOn();

	/** Logic that holds the rules for locking on the Enemy*/
	void LockOnLogic();

	/** Exec function that makes the character Dash*/
	UFUNCTION(BlueprintCallable, Category = Dash)
	void Dash();

	UFUNCTION(BlueprintCallable, Category = EnemySearch)
	void DetectEnemy();

	/** Begin Play Native UE4 function*/
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
    
    
private:
    
    /** Health value for the Player */
    int32 Health;
    
    /** Armor value for the Player */
    int32 Armor;
    
    /** int value that hold the Maximum Health */
    int32 MaxHealth;
    
    /** int value that holds the Maximum Armor */
    int32 MaxArmor;

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

	void EndGame();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
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
    /** Gets teh MaxArmor Value for this Character */
    FORCEINLINE int32 GetMaxArmor() const { return MaxArmor; }
};

