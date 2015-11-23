// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ParticleDefinitions.h"
#include "WeaponProjectile.generated.h"

UCLASS()
class TITANBOTS_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* AuraParticle;
    
private:
    
    /** Damage count necessary to find out how much damage it does*/
    int32 DamageAmount;
    
    /** Size of the explosion particle on Collision*/
    int32 ExplosionSize;

public:
	// Sets default values for this actor's properties
	AWeaponProjectile(const FObjectInitializer& ObjectInitializer);

	/** called when projectile hits something */
	UFUNCTION()
	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    /** Sets the amount for DamageAmount
     * @param NewAmount  value for the new DamageAmount
     */
    void SetDamageAmount(int32 NewAmount);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UParticleSystemComponent* GetAuraParticle() const { return AuraParticle; }
    /** Gets the DamageAmount Variable */
    FORCEINLINE int32 GetDamageAmount() const { return DamageAmount; }
    /** Gets the ExplosionSize Variable */
    FORCEINLINE int32 GetExplosionSize() const { return ExplosionSize; }

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
