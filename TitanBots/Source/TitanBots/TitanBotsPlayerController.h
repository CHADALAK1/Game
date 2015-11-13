// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Networking.h"
#include "Sockets.h"
#include "TitanBotsCharacter.h"
#include "GaragePawn.h"
#include "TitanBotsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TITANBOTS_API ATitanBotsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	//Constructor
	ATitanBotsPlayerController();

	//Light Character class Declaration
	TSubclassOf<ATitanBotsCharacter> LightChar;

	//Medium Character Class Declaration
	TSubclassOf<ATitanBotsCharacter> MediumChar;

	USkeletalMesh *LightMesh;
	USkeletalMesh *MediumMesh;

	//Turns on and off the garage menu
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Garage)
	bool bIsInGarage;

	virtual void BeginPlay() override;

	FTimerHandle Timer01;
	FTimerHandle Timer02;

	FSocket* ConnectionSocket;
	FIPv4Endpoint RemoteAddressForConnection;


	//Timer functions, could be threads
	void TCPConnectionListener(); 	
	void TCPSocketListener();		

	//Checks the String information from the NFC
	void NFCIDCheck(FString ID);


	//Converts Binary Array into a String (VERY CRUCIAL)
	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray);
	
};
