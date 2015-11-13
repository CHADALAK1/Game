// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include "GaragePawn.h"


// Sets default values
AGaragePawn::AGaragePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

}

// Called when the game starts or when spawned
void AGaragePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGaragePawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AGaragePawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

