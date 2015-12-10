// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TitanBots.h"
#include "EnemyAIController.h"
#include "TitanBotsPlayerController.h"
#include "TitanBotsGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "TitanBotsCharacter.h"

//////////////////////////////////////////////////////////////////////////
// ATitanBotsCharacter

ATitanBotsCharacter::ATitanBotsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 350.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
    
    Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
    Collision->AttachTo(RootComponent);
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ATitanBotsCharacter::OnEnterCollision);

	ProjSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjSpawn"));
	ProjSpawn->AttachTo(RootComponent);

	bUseControllerRotationYaw = true;

    MaxHealth = 100;
    MaxArmor = 100;
    
    Health = 100;
    Armor = 100;
    
	bIsLockedOn = false;
	bIsDead = false;
	bIsSpecial = false;

	CamLocY = 0.f;
	CamLocZ = 0.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATitanBotsCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    InputComponent->BindAction("Action", IE_Pressed, this, &ATitanBotsCharacter::Fire);
    InputComponent->BindAction("Action", IE_Released, this, &ATitanBotsCharacter::StopFire);
	InputComponent->BindAction("Special", IE_Pressed, this, &ATitanBotsCharacter::SpecialStart);
	InputComponent->BindAction("Special", IE_Released, this, &ATitanBotsCharacter::SpecialStop);
	InputComponent->BindAction("ExitGame", IE_Pressed, this, &ATitanBotsCharacter::EndGame);
	InputComponent->BindAction("LockOn", IE_Pressed, this, &ATitanBotsCharacter::LockOn);
	InputComponent->BindAction("Dash", IE_Pressed, this, &ATitanBotsCharacter::Dash);

	InputComponent->BindAxis("MoveForward", this, &ATitanBotsCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATitanBotsCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ATitanBotsCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ATitanBotsCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &ATitanBotsCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ATitanBotsCharacter::TouchStopped);
}

void ATitanBotsCharacter::BeginPlay()
{

}

void ATitanBotsCharacter::DetectEnemy()
{
	//if this Character is being possessed by the player
	if (this->GetController()->IsA(ATitanBotsPlayerController::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "FOUND Player");
		//Get all TitanBotsCharactter Actors on the scene
		for (TActorIterator<ATitanBotsCharacter> Itr(GetWorld()); Itr; ++Itr)
		{
			//If one of them is being controlled by a EnemyAIController
			if (Itr->GetController()->IsA(AEnemyAIController::StaticClass()))
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "FOUND ENEMY");
				//Store iterated Character in Enemy Pawn (must dereference the Iterator to store in EnemyPawn)
				EnemyPawn = *Itr;

			}
		}
	}
}

void ATitanBotsCharacter::Tick(float DeltaSeconds)
{
	LockOnLogic();
}

void ATitanBotsCharacter::EndGame()
{
	ATitanBotsGameMode *GM = (ATitanBotsGameMode*)GetWorld()->GetAuthGameMode();
	GM->CloseNFCTech();
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void ATitanBotsCharacter::Fire()
{
	if (!IsSpecial())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Fire");
		FActorSpawnParameters Params;
		Params.Instigator = this;
		Params.Owner = this;
		AWeaponProjectile *Proj = GetWorld()->SpawnActor<AWeaponProjectile>(WeapProj, GetProjSpawn()->GetComponentLocation(), GetFollowCamera()->GetForwardVector().Rotation(), Params);
		if (Proj)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "SPAWN");
			PlaySound(FireSound);
		}
	}
}

void ATitanBotsCharacter::StopFire()
{
	if (!IsSpecial())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "StopFire");
	}
}
void ATitanBotsCharacter::SpecialStart()
{
	SetIsSpecial(true);
}

void ATitanBotsCharacter::SpecialStop()
{
	SetIsSpecial(false);
}

void ATitanBotsCharacter::LockOn()
{
	if (!bIsLockedOn)
	{
		bIsLockedOn = true;
	}
	else
	{
		bIsLockedOn = false;
	}
}

void ATitanBotsCharacter::LockOnLogic()
{
	//if we are locked on
	if (bIsLockedOn)
	{
		//if we have an enemy in the World
		if (EnemyPawn != NULL)
		{
			CamLocZ = FMath::FInterpTo(CamLocZ, 200.f, GetWorld()->GetDeltaSeconds(), 3.0f);
			CamLocY = FMath::FInterpTo(CamLocY, 0.f, GetWorld()->GetDeltaSeconds(), 3.0f);
			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EnemyPawn->GetActorLocation());
			GetCameraBoom()->SetRelativeLocation(FVector(0, 0, CamLocZ));
			SetActorRotation(FRotator(0,Rotation.Yaw,0));
			this->GetController()->SetControlRotation(Rotation);
		}
	}
	else
	{
		CamLocZ = FMath::FInterpTo(CamLocZ, 10.f, GetWorld()->GetDeltaSeconds(), 3.0f);
		CamLocY = FMath::FInterpTo(CamLocY, 75.f, GetWorld()->GetDeltaSeconds(), 3.0f);
		GetCameraBoom()->SetRelativeLocation(FVector(0, CamLocY, CamLocZ));
	}
}

void ATitanBotsCharacter::SetArmor(int32 NewArmor)
{
    if(NewArmor >= 0 && NewArmor <= GetMaxArmor())
    {
        Armor = NewArmor;
    }
}

void ATitanBotsCharacter::SetHealth(int32 NewHealth)
{
    if(NewHealth >= 0 && NewHealth <=GetMaxHealth())
    {
        Health = NewHealth;
    }
}

void ATitanBotsCharacter::SetEnergy(int32 NewEnergy)
{
	if (NewEnergy >= 0 && NewEnergy <= GetMaxEnergy())
	{
		Energy = NewEnergy;
	}
}

void ATitanBotsCharacter::SetIsDead(bool Set)
{
	bIsDead = Set;
}

void ATitanBotsCharacter::AddHealth(int32 Amount)
{
    if((GetHealth() + Amount) < GetMaxHealth())
    {
        Health += Amount;
    }
    else
    {
        Health = 100;
    }
}

void ATitanBotsCharacter::DecreaseHealth(int32 Amount)
{
	if (!IsInvulnerable())
	{
		if ((GetHealth() - Amount) > 0)
		{
			Health -= Amount;
		}
		else
		{
			Health = 0;
			SetIsDead(true);
			GetCharacterMovement()->DisableMovement();
		}
	}
}

void ATitanBotsCharacter::AddArmor(int32 Amount)
{
    if((GetArmor() + Amount) < GetMaxArmor())
    {
        Armor += Amount;
    }
    else
    {
        Armor = 100;
    }
}

void ATitanBotsCharacter::DecreaseArmor(int32 Amount)
{
	if (!IsInvulnerable())
	{
		if ((GetArmor() - Amount) > 0)
		{
			Armor -= Amount;
		}
		else
		{
			Armor = 0;
		}
	}
}

void ATitanBotsCharacter::AddEnergy(int32 Amount)
{
	if ((GetEnergy() + Amount) < GetMaxEnergy())
	{
		Energy += Amount;
	}
	else
	{
		Energy = GetMaxEnergy();
	}
}

void ATitanBotsCharacter::DecreaseEnergy(int32 Amount)
{
	if ((GetEnergy() - Amount) > 0)
	{
		Energy -= Amount;
	}
	else
	{
		Energy = 0;
	}
}

void ATitanBotsCharacter::SetMaxEnergy(int32 NewMaxEnergy)
{
	MaxEnergy = NewMaxEnergy;
}

void ATitanBotsCharacter::SetMaxHealth(int32 NewMaxHealth)
{
    if(NewMaxHealth >= 1)
    {
        MaxHealth = NewMaxHealth;
    }
    else
    {
        MaxHealth = 1;
    }
}

void ATitanBotsCharacter::SetMaxArmor(int32 NewMaxArmor)
{
    if(NewMaxArmor >= 1)
    {
        MaxArmor = NewMaxArmor;
    }
    else
    {
        MaxArmor = 1;
    }
}

void ATitanBotsCharacter::SetIsInvulnerable(bool Set)
{
	bIsInvulnerable = Set;
}

float ATitanBotsCharacter::GetHealthPercentage()
{
    return FMath::GetRangePct(0.f, MaxHealth, Health);
}

float ATitanBotsCharacter::GetArmorPercentage()
{
    return FMath::GetRangePct(0.f, MaxArmor, Armor);
}

float ATitanBotsCharacter::GetEnergyPercentage()
{
	return FMath::GetRangePct(0.f, MaxEnergy, Energy);
}

bool ATitanBotsCharacter::IsSpecial()
{
	return bIsSpecial;
}

void ATitanBotsCharacter::SetIsSpecial(bool Special)
{
	bIsSpecial = Special;
}

void ATitanBotsCharacter::Dash()
{
	//if we are not in the air
	if (!GetCharacterMovement()->IsFalling())
	{
		//if we are moving
		if (GetCharacterMovement()->Velocity != FVector(0, 0, 0))
		{
			//Get the rotation, but only control the Yaw value
			FRotator DashAngle = FRotator(0, GetControlRotation().Yaw, 0);

			FVector DashVector;
			//Find out which direction we are moving
			if (AngleY > 0.5f)
			{
				DashVector = DashAngle.RotateVector(FVector(0, 5000.f, 0));
			}
			else if (AngleY < -0.5f)
			{
				DashVector = DashAngle.RotateVector(FVector(0, -5000.f, 0));
			}
			//Launch the character to simulate Dash
			LaunchCharacter(DashVector, false, false);
		}
	}
}

void ATitanBotsCharacter::OnEnterCollision(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ATitanBotsCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void ATitanBotsCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void ATitanBotsCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATitanBotsCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATitanBotsCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		//Set the X direction for the AngleX value
		AngleX = Value;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATitanBotsCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		//Set the Y direction for the AngleY value
		AngleY = Value;
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

UAudioComponent *ATitanBotsCharacter::PlaySound(USoundCue *Sound)
{
	UAudioComponent *AC = NULL;
	if (Sound)
	{
		AC = UGameplayStatics::SpawnSoundAttached(Sound, GetRootComponent(), FName("NAME_None"), FVector(), EAttachLocation::SnapToTarget, false, 1.0f, this->GetActorTimeDilation(), 0.0f, NULL);
	}
	return AC;
}
