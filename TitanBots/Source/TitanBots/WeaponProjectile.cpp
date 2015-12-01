// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "TitanBotsCharacter.h"
#include "WeaponProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AWeaponProjectile::AWeaponProjectile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Use a sphere as a simple collision representation
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("DefaultProjectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AWeaponProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	CollisionComp->IgnoreActorWhenMoving(GetInstigator(), true);

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	AuraParticle = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("AuraParticle"));
	AuraParticle->AttachTo(RootComponent);

	SetDamageAmount(10);

}

void AWeaponProjectile::BeginPlay()
{
	GetCollisionComp()->MoveIgnoreActors.Add(GetInstigator());
}

void AWeaponProjectile::Tick(float DeltaSeconds)
{

}

void AWeaponProjectile::SetDamageAmount(int32 NewAmount)
{
    if(NewAmount >= 0)
    {
        DamageAmount = NewAmount;
    }
    else
    {
        DamageAmount = 0;
    }
}

void AWeaponProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult)
{
	ATitanBotsCharacter *Char = Cast<ATitanBotsCharacter>(OtherActor);
	
	if (Char)
	{
		if (Char != GetInstigator())
		{
			Char->DecreaseHealth(DamageAmount);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "HIT");
			Destroy();
		}
	}
	else
	{
		Destroy();
	}
}
