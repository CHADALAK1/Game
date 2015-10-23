// Fill out your copyright notice in the Description page of Project Settings.

#include "TitanBots.h"
#include <string>
#include <cstdlib>
#include "TitanBotsPlayerController.h"


ATitanBotsPlayerController::ATitanBotsPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> LightPawnBP(TEXT("Blueprint'/Game/ThirdPerson/Blueprints/Pawns/LightPawn_BP.LightPawn_BP'"));
	static ConstructorHelpers::FObjectFinder<UBlueprint> MediumPawnBP(TEXT("Blueprint'/Game/ThirdPerson/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter'"));
	if (LightPawnBP.Object)
	{
		LightChar = (UClass*)LightPawnBP.Object->GeneratedClass;
	}
	if (MediumPawnBP.Object)
	{
		MediumChar = (UClass*)MediumPawnBP.Object->GeneratedClass;
	}


}

void ATitanBotsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TCPConnectionListener();
}


//TCP Connection Listener
void ATitanBotsPlayerController::TCPConnectionListener()
{

	//Create a socket connection to the NFC-Plugin
	ConnectionSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address ip;
	FString address = TEXT("127.0.0.1");
	FIPv4Address::Parse(address, ip);
	RemoteAddress->SetIp(ip.GetValue());
	RemoteAddress->SetPort(7000);

	//Connect to the 127.0.0.1 7000 Port
	bool Pending = ConnectionSocket->Connect(*RemoteAddress);

	// if we are connected to the port
	if (Pending)
	{
		if (ConnectionSocket != NULL)
		{
			//Global cache of current Remote Address
			RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);

			//Make limitless timer to receive FString information
			GetWorldTimerManager().SetTimer(Timer02, this, &ATitanBotsPlayerController::TCPSocketListener, 0.01, true);
		}

	}
}


//This function requires
//		#include <string>
FString ATitanBotsPlayerController::StringFromBinaryArray(const TArray<uint8>& BinaryArray)
{
	//Create a string from a byte array!
	std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()), BinaryArray.Num());
	return FString(cstr.c_str());
}


void ATitanBotsPlayerController::TCPSocketListener()
{
	//~~~~~~~~~~~~~
	if (!ConnectionSocket) return;
	//~~~~~~~~~~~~~


	//Binary Array!
	TArray<uint8> ReceivedData;

	uint32 Size;
	while (ConnectionSocket->HasPendingData(Size))
	{
		ReceivedData.Init(FMath::Min(Size, 65507u));

		int32 Read = 0;
		ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (ReceivedData.Num() <= 0)
	{
		//No Data Received
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Bytes Read ~> %d"), ReceivedData.Num()));


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//						String From Binary Array
	const FString ReceivedUE4String = StringFromBinaryArray(ReceivedData);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ATitanBotsCharacter *Char = (ATitanBotsCharacter*)this->GetControlledPawn();

	Char->CharacterMeshID = ReceivedUE4String;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("As String Data ~> %s"), *ReceivedUE4String));

	NFCIDCheck(ReceivedUE4String);
}

void ATitanBotsPlayerController::NFCIDCheck(FString ID)
{
	ATitanBotsCharacter *Char = (ATitanBotsCharacter*)this->GetControlledPawn();
	
	//Trims the unnecessary fat from the NFC String (WILL CHANGE LATER AFTER PROTOTYPE STAGE FOR UPGRADES
	ID.RemoveAt(0, 13);
	ID.RemoveAt(5, 17);

	//Displays the NFC String for debugging purposes
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, ID);

	//If we are currently possessing a Character
	if (Char != NULL)
	{
		if (ID.Equals("dc6b0"))
		{
			UnPossess();
			FVector loc = Char->GetActorLocation();
			FRotator rot = Char->GetActorRotation();
			Char->Destroy();
			Char = GetWorld()->SpawnActor<ATitanBotsCharacter>(LightChar, loc,rot);
			Possess(Char);
		}
		if (ID.Equals("3748a"))
		{
			UnPossess();
			FVector loc = Char->GetActorLocation();
			FRotator rot = Char->GetActorRotation();
			Char->Destroy();
			Char = GetWorld()->SpawnActor<ATitanBotsCharacter>(MediumChar, loc, rot);
			Possess(Char);
		}
	}
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             