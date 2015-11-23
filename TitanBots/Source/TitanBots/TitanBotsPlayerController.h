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

UENUM(BlueprintType)
enum ClassType
{
	E_None		UMETA(DisplayName = "None"),
	E_Light		UMETA(DisplayName = "Light"),
	E_Medium	UMETA(DisplayName = "Medium"),
	E_Heavy		UMETA(DisplayName = "Heavy")
};

UCLASS()
class TITANBOTS_API ATitanBotsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	//Constructor
	ATitanBotsPlayerController();

	/*Light Character class Declaration */
	TSubclassOf<ATitanBotsCharacter> LightChar;

	/*Medium Character Class Declaration */
	TSubclassOf<ATitanBotsCharacter> MediumChar;

    /** Light Mesh SkeletalMesh to call in the ConstructorHelper ObjectFinder */
	USkeletalMesh *LightMesh;
    
    /** Medium Mesh SkeletalMesh to call in the ConstructorHelper ObjectFinder */
	USkeletalMesh *MediumMesh;

	//Turns on and off the garage menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Garage)
	bool bIsInGarage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Garage)
	TEnumAsByte<ClassType> TypeClass;

	virtual void BeginPlay() override;

	FTimerHandle Timer01;
	FTimerHandle Timer02;

    /* Socket to connect to the NFC Plug-In */
	FSocket* ConnectionSocket;
	FIPv4Endpoint RemoteAddressForConnection;


	/* Creates Socket and checks for connection to start timer for The Socket Listener */
	void TCPConnectionListener();
    
    /* Keeps listening and decodes the low level string value from the NFC to UE4 */
	void TCPSocketListener();		

	/*Checks the String information from the NFC */
	void NFCIDCheck(FString ID);


	//Converts Binary Array into a String (VERY CRUCIAL)
	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray);
	
};
